#include <jni.h>
#include <errno.h>

#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <thread>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <sys/uio.h>

#include <fcntl.h>
#include <android/log.h>
#include <pthread.h>
#include <dirent.h>
#include <list>
#include <libgen.h>

#include <sys/mman.h>
#include <sys/wait.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>

#include <codecvt>
#include <chrono>
#include <queue>

#include "ImGui/imgui_internal.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_android.h"
#include "ImGui/imgui_impl_opengl3.h"

#include <EGL/egl.h>
#include <GLES3/gl3.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <sys/system_properties.h>

//====================================
#include "ImGui/FONTS/DEFAULT.h"
//=====================================

int screenWidth = 0;
int screenHeight = 0;
bool g_Initialized = false;
ImGuiWindow * g_window = NULL;

float num1 = 0.0f, num2 = 0.0f;
char operation = '+';
float result = 0.0f;
bool calculated = false;

void showCalculator() {
    ImGuiIO &io = ImGui::GetIO();
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(868, 562));
    if (ImGui::Begin("Calculator", 0, ImGuiWindowFlags_NoSavedSettings)) {
        g_window = ImGui::GetCurrentWindow();
        ImGui::InputFloat("Num 1", & num1);
        ImGui::InputFloat("Num 2", & num2);
        ImGui::Text("Operation");
        if (ImGui::Button("+"))
            operation = '+';
        ImGui::SameLine();
        if (ImGui::Button("-"))
            operation = '-';
        ImGui::SameLine();
        if (ImGui::Button("*"))
            operation = '*';
        ImGui::SameLine();
        if (ImGui::Button("/"))
            operation = '/';
        if (ImGui::Button("Calculate")) {
            switch (operation) {
                case '+':
                    result = num1 + num2;
                    break;
                case '-':
                    result = num1 - num2;
                    break;
                case '*':
                    result = num1 * num2;
                    break;
                case '/':
                    result = num1 / num2;
                    break;
            }
            calculated = true;
        }
        if (calculated) {
            ImGui::Text("Result: %.3f", result);
        }
    }
    ImGui::End();
}

extern "C" JNIEXPORT void JNICALL
Java_com_imgui_calculator_GLES3JNIView_init(JNIEnv * env, jclass cls) {
    //SetUpImGuiContext
    if (g_Initialized) return ;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO & io = ImGui::GetIO();
    //Set ImGui Style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplAndroid_Init();
    ImGui_ImplOpenGL3_Init("#version 300 es");
    ImGui::GetStyle().ScaleAllSizes(3.0f);
    static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0x0900, 0x097F, 0,};
    ImFontConfig font_config;
    ImFontConfig icons_config;
    ImFontConfig CustomFont;
    CustomFont.FontDataOwnedByAtlas = false;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 2;
    icons_config.OversampleV = 2;
    io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom3), sizeof(Custom3), 30.f, & CustomFont);
    g_Initialized = true;
}

extern "C" JNIEXPORT void JNICALL
Java_com_imgui_calculator_GLES3JNIView_resize(JNIEnv * env, jobject obj, jint width, jint height) {
    screenWidth = (int) width;
    screenHeight = (int) height;
    glViewport(0, 0, width, height);
    ImGuiIO & io = ImGui::GetIO();
    io.ConfigWindowsMoveFromTitleBarOnly = true;
    io.IniFilename = NULL;
    ImGui::GetIO().DisplaySize = ImVec2((float)width, (float)height);
}

extern "C" JNIEXPORT void JNICALL
Java_com_imgui_calculator_GLES3JNIView_step(JNIEnv * env, jobject obj) {
    ImGuiIO & io = ImGui::GetIO();
    static bool show_MainMenu_window = true;
    //Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(screenWidth,  screenHeight);//？Settings window
    ImGui::NewFrame();
    if (show_MainMenu_window) {
        showCalculator();
    }
    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

extern "C" JNIEXPORT void JNICALL Java_com_imgui_calculator_GLES3JNIView_imgui_Shutdown(JNIEnv * env, jobject obj) {
    if (!g_Initialized)
        return;
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
    g_Initialized = false;
}

extern "C" JNIEXPORT void JNICALL Java_com_imgui_calculator_GLES3JNIView_MotionEventClick(JNIEnv * env, jobject obj, jboolean down, jfloat PosX, jfloat PosY) {
    ImGuiIO & io = ImGui::GetIO();
    io.MouseDown[0] = down;
    io.MousePos = ImVec2(PosX, PosY);
}

extern "C" JNIEXPORT jstring JNICALL Java_com_imgui_calculator_GLES3JNIView_getWindowRect(JNIEnv * env, jobject thiz) {
    char result[256] = "0|0|0|0";
    if (g_window) {
        sprintf(result, "%d|%d|%d|%d", (int)g_window->Pos.x, (int)g_window->Pos.y, (int)g_window->Size.x, (int)g_window->Size.y);
    }
    return env->NewStringUTF(result);
}