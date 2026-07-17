#ifndef ABCD
#   include <glfw3.h>
#   include <glm/glm.hpp>
#   include <stb/stb.h>
#   include <nlohmann/json.hpp>
#   include <iostream>
#   include <chrono>
#   include <ctime>
#   include <time.h>
#   include <iomanip>
#   include <mutex>
#   include <sstream>
#   include <string>
#   include <fstream>
#   include <unordered_map>
#   include <memory>
#   include <windows.h>
#   include <glm/glm.hpp>
#   include <glm/gtc/type_ptr.hpp>
#   include <glm/gtc/matrix_transform.hpp>
#   include <format>
#   endif
#ifdef __Mistical__
#   warning MisticalGL was already included!
#   endif
#ifndef __Mistical__
#   define __Mistical__
#   endif
#include <string>
#include <vector>
#include <utility>
#include <initializer_list>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <thread>
#include <windows.h>

namespace Mistical {
    /*class Console {
        public:
            #define TRACE(msg, ...)          _log("       ", msg, TEXT_COLOR_WHITE, ##__VA_ARGS__);
            #define LOG(msg, ...)            _log("LOG:   ", msg, TEXT_COLOR_WHITE, ##__VA_ARGS__);
            #define WARN(msg, ...)           _log("WARN:  ", msg, TEXT_COLOR_YELLOW, ##__VA_ARGS__);
            #define ERROR(msg, ...)          _log("ERROR: ", msg, TEXT_COLOR_BRIGHT_RED, ##__VA_ARGS__);
            #define CRITICAL_ERROR(msg, ...) _log("CRIT:  ", msg, TEXT_COLOR_RED, ##__VA_ARGS__);
            // inline static void trace            (const char* mnsg, ...) {_log("       ", msg, TEXT_COLOR_WHITE, ...);}
            // inline static void log              (const char* mnsg, ...) {_log("LOG:   ", msg, TEXT_COLOR_WHITE, ...);}
            // inline static void warn             (const char* mnsg, ...) {_log("WARN:  ", msg, TEXT_COLOR_YELLOW, ...);}
            // inline static void error            (const char* mnsg, ...) {_log("ERROR: ", msg, TEXT_COLOR_BRIGHT_RED, ...);}
            // inline static void criticalError    (const char* mnsg, ...) {_log("CRIT:  ", msg, TEXT_COLOR_RED, ...);}
            //template <typename... Args> inline static void trace(std::format_string<Args...> fmt, Args&&... args)            { _log("       ", std::format(fmt, std::forward<Args>(args)...), TEXT_COLOR_WHITE); }
            //template <typename... Args> inline static void log(std::format_string<Args...> fmt, Args&&... args)              { _log("LOG:   ", std::format(fmt, std::forward<Args>(args)...), TEXT_COLOR_WHITE); }
            //template <typename... Args> inline static void warn(std::format_string<Args...> fmt, Args&&... args)             { _log("WARN:  ", std::format(fmt, std::forward<Args>(args)...), TEXT_COLOR_YELLOW); }
            //template <typename... Args> inline static void error(std::format_string<Args...> fmt, Args&&... args)            { _log("ERROR: ", std::format(fmt, std::forward<Args>(args)...), TEXT_COLOR_BRIGHT_RED); }
            //template <typename... Args> inline static void criticalError(std::format_string<Args...> fmt, Args&&... args)    { _log("CRIT:  ", std::format(fmt, std::forward<Args>(args)...), TEXT_COLOR_RED); }
        private:
            enum TextColor {
                TEXT_COLOR_BLACK,   TEXT_COLOR_BRIGHT_BLACK,
                TEXT_COLOR_RED,     TEXT_COLOR_BRIGHT_RED,
                TEXT_COLOR_GREEN,   TEXT_COLOR_BRIGHT_GREEN,
                TEXT_COLOR_YELLOW,  TEXT_COLOR_BRIGHT_YELLOW,
                TEXT_COLOR_BLUE,    TEXT_COLOR_BRIGHT_BLUE,
                TEXT_COLOR_MAGENTA, TEXT_COLOR_BRIGHT_MAGENTA,
                TEXT_COLOR_CYAN,    TEXT_COLOR_BRIGHT_CYAN,
                TEXT_COLOR_WHITE,   TEXT_COLOR_BRIGHT_WHITE,
                TEXT_COLOR_COUNT 
            };
            template <typename ...Args>
            void _log(const char* prefix, const char* msg, TextColor textColor, Args... args) {
                std::cout << msg << args;
            }
    };*/
    class Console {
        public:
            template<typename... Args> static void trace(const char* format, Args... args) {
                print(WHITE, "         ", format, args...);
            }
            template<typename... Args> static void log(const char* format, Args... args) {
                print(WHITE, "[LOG]    ", format, args...);
            }
            template<typename... Args> static void warn(const char* format, Args... args) {
                print(YELLOW, "[WARN]   ", format, args...);
            }
            template<typename... Args> static void error(const char* format, Args... args) {
                print(LIGHT_RED, "[ERROR]  ", format, args...);
            }
            template<typename... Args> static void criticalError(const char* format, Args... args) {
                print(DARK_RED, "[CRIT]   ", format, args...);
            }
            template<typename... Args> static void debug(const char* format, Args... args) {
                print(PURPLE, "[DEBUG]  ", format, args...);
            }
        private:
            static constexpr WORD WHITE      = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            static constexpr WORD YELLOW     = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            static constexpr WORD LIGHT_RED  = FOREGROUND_RED | FOREGROUND_INTENSITY;
            static constexpr WORD DARK_RED   = FOREGROUND_RED;
            static constexpr WORD PURPLE     = FOREGROUND_RED | FOREGROUND_BLUE;
            static inline std::mutex mutex;
            static std::string getTime() {
                auto now = std::chrono::system_clock::now();
                auto tt = std::chrono::system_clock::to_time_t(now);

                std::tm tm{};
                #ifdef _WIN32
                    localtime_s(&tm, &tt);
                #else
                    localtime_r(&tt, &tm);
                #endif

                std::ostringstream oss;
                oss << std::put_time(&tm, "%H:%M:%S");

                return oss.str();
            }
            template<typename... Args> static void print(WORD color, const char* type, const char* format, Args... args) {
                std::lock_guard<std::mutex> lock(mutex);

                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

                char buffer[4096];
                std::snprintf(buffer, sizeof(buffer), format, args...);

                SetConsoleTextAttribute(hConsole, color);

                    std::cout << getTime() << " "
                            << type << ""
                            << buffer << "\n";

                SetConsoleTextAttribute(hConsole, WHITE);
            }
    };
    class Opengl {
        public:
            struct WindowSettings{
                bool focused;
                bool iconifined;
                bool resizeable;
                bool visible;
                bool decorated;
                bool autoIconify;
                bool floating;
                bool maximazed;
                bool centerCursor;
                std::string iconPath;
            };
            void initGLFW(bool initGLFW = true, int verMinor = 3, int verMajor = 3) {
                if (initGLFW == true) {
                    glfwInit();
                }
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, verMinor);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, verMajor);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            }

            void initGLAD() {
                std::cout << "initGLAD() " << glfwGetProcAddress << "\n"; 
                if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                    //Console.CRITICAL_ERROR("Failed to initialize GLAD");
                    std::cout << "Failed to initialize GLAD\n";
                }
            }

            GLFWwindow* createWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share, WindowSettings windowSettings = {resizeable: true, iconPath: ""}) {
                GLFWwindow* res = glfwCreateWindow(width, height, title, monitor, share);
                glfwWindowHint(GLFW_RESIZABLE, windowSettings.resizeable);
                if (windowSettings.iconPath != "") {
                    GLFWimage images[1];
                    int iconWidth, iconHeight, iconChannels;
                    unsigned char* iconPixels = stbi_load(windowSettings.iconPath.c_str(), &iconWidth, &iconHeight, &iconChannels, 4);
                    images[0].width = iconWidth;
                    images[0].height = iconHeight;
                    images[0].pixels = iconPixels;
                    glfwSetWindowIcon(res, 1, images); //Set all of this to Image.load() later..
                } else {
                    glfwSetWindowIcon(res, 0, NULL);
                }
                return res;
            }
        private:
            
                //Mistical::Console Console;
    };
    class Image {
        public:
            GLFWimage load(std::string path, int req_comp = 4) {
                GLFWimage image;
                int imgWidth, imgHeight, imgComp;
                unsigned char* imgPixels = stbi_load(path.c_str(), &imgWidth, &imgHeight, &imgComp, req_comp);
                image.width = imgWidth;
                image.height = imgHeight;
                image.pixels = imgPixels;
                return image;
            }
        private:
    };
    class Key {
        #define IS_RELEASED     0
        #define IS_PRESSED      1
        #define IS_REPEATING    2
        public:
            bool isReleased(GLFWwindow* window, int key) {
                if (glfwGetKey(window, key) == GLFW_RELEASE) { return true; }
                return false;
            }
            bool isPressed(GLFWwindow* window, int key) {
                if (glfwGetKey(window, key) == GLFW_PRESS) { return true; }
                return false;
            }
            bool isRepeating(GLFWwindow* window, int key) {
                if (glfwGetKey(window, key) == GLFW_REPEAT) { return true; }
                return false;
            }
            bool wasPressed(GLFWwindow* window, int key) {
                if (glfwGetKey(window, key) == GLFW_PRESS && pressedKeys[key] == false) {
                    pressedKeys[key] = true;
                    return true;
                }
                checkKeyPress(window, key);
                return false;
            }
            bool wasReleased(GLFWwindow* window, int key) {
                if (glfwGetKey(window, key) == GLFW_RELEASE && pressedKeys[key] == true) {
                    pressedKeys[key] = false;
                    return true;
                }
                checkKeyPress(window, key);
                return false;
            }
        private:
            bool pressedKeys[349];
            void checkKeyPress(GLFWwindow* window, int key) {
                if (glfwGetKey(window, key) == GLFW_PRESS) {
                    pressedKeys[key] = true;
                    return;
                }
                pressedKeys[key] = false;
            }
    };
    class JSON {
        public:
            static nlohmann::json ParseJSONFile(std::string filePath) {
                try {
                    std::ifstream JSONFile(filePath);
                    if (!JSONFile.is_open()) {
                        return {{"result", NULL}};
                    }
                    nlohmann::json returnJSON;
                    JSONFile >> returnJSON;
                    return returnJSON;
                } catch (std::exception const& e) {
                    Console::error("Failed to load JSON \"%s\"", filePath);
                }
        }
        private:
        
    };
    class Lang {
        public:
            enum Langs {
                CS_CZ,
                EN_AU,
                EN_GB,
                EN_US,
                JA_JP
            };
            std::string getTranslationKey(std::string key) {
                nlohmann::json langJSON = getSelectedLangJSON();
                return langJSON[key].get<std::string>().c_str();
            }
            void setSelectedLang(enum Langs lang) {
                selectedLang = lang;
                selectedLangJSON = jsonClass.ParseJSONFile(langsFilepath + langNames[lang] + ".json");
            }
            Langs getSelectedLang() {
                return selectedLang;
            }
            nlohmann::json getSelectedLangJSON() {
                return selectedLangJSON;
            }
        private:
            Langs selectedLang;
            nlohmann::json selectedLangJSON;
            const std::string langsFilepath = "./data/lang/";
            Mistical::JSON jsonClass;
            const char* langNames[5] = {
                "CS_CZ",
                "EN_AU",
                "EN_GB",
                "EN_US",
                "JA_JP"
            };
    };
    class ColorClass {
        public:
        private:
    };
    class Window {
        public:
            int pos[2];
            int height = 512;
            int width = 512;
            const char* title = "Window";
            GLFWimage* icons;
            GLFWmonitor* monitor = NULL;
            GLFWwindow* share = NULL;
            GLFWwindow* window;
            double cursorPos[2] = {0, 0};
            int cursorMode = GLFW_CURSOR;
            void init();
            void init(int pWidth, int pHeight, const char* pTitle);
            void init(int pWidth, int pHeight, const char* pTitle, GLFWimage* pIcons);
            void init(int pWidth, int pHeight, const char* pTitle, GLFWmonitor* pMonitor, GLFWwindow* pShare);
            void init(int pWidth, int pHeight, const char* pTitle, GLFWimage* pIcons, GLFWmonitor* pMonitor, GLFWwindow* pShare);
            void update();
            void swapBuffers();
            void moveTo(int x, int y);
            void minimalize();
            void unMinimalize();
            void hide();
            void show();
            void focus();
            void requestAttention();
            void setPositionCallback(GLFWwindowposfun callback);
            void setSizeCallback(GLFWwindowsizefun callback);
            void setMinimalizationCallback(GLFWwindowiconifyfun callback);
            void setFocusCallback(GLFWwindowfocusfun callback);
            void setCloseCallback(GLFWwindowclosefun callback);
            void setCursorPosCallback(GLFWcursorposfun callback);
            void setIconsFromPath(const char** path, int count);
            void setAttribute(int attrib, int value);
            void setPos(int x, int y);
            void setSize(int w, int h);
            void setSizeLimits(int minW, int minH, int maxW, int maxH);
            void setCursor(int cursor);
            void setCursor(int cursor, int mode);
            void removeSizeLimits();
            void setTitle(const char* t);
            int getAttribute(int attribute);
            //int* getPos();
            //int* getSize();
            int getPosX();
            int getPosY();
            int getHeight();
            int getWidth();
            const char* getTitle();
            bool shouldClose();
            void destroy();
            void close();
            class WindowInput {
                public:
                    WindowInput(Window& w) : window(w), key(w), mouse(w) {}
                    class WindowInputKey {
                        public:
                            WindowInputKey(Window& w) : window(w) {}
                            bool isReleased(int key);
                            bool isPressed(int key);
                            bool isRepeating(int key);
                            bool wasPressed(int key);
                            bool wasReleased(int key);
                        private:
                            Window& window;
                            void checkKeyPress(int key);
                            bool pressedKeys[349];
                    };
                    class WindowInputMouse {
                        public:
                            WindowInputMouse(Window& w) : window(w) {}
                            bool isReleased(int btn);
                            bool isPressed(int btn);
                            bool wasReleased(int btn);
                            bool wasPressed(int btn);
                        private:
                            Window& window;
                    };
                    WindowInputKey key;
                    WindowInputMouse mouse;
                private:
                    Window& window;
            };

            WindowInput input;
            Window() : input(*this) {}
        private:
            bool fullScreen = false;
    };
    void Window::init() {
        window = glfwCreateWindow(width, height, title, monitor, share);
    }
    void Window::init(int pWidth, int pHeight, const char* pTitle) {
        height = pHeight;
        width = pWidth;
        title = pTitle;
        window = glfwCreateWindow(width, height, title, monitor, share);
    }
    void Window::init(int pWidth, int pHeight, const char* pTitle, GLFWimage* pIcons) {
                height = pHeight;
                width = pWidth;
                title = pTitle;
                icons = pIcons;
                window = glfwCreateWindow(width, height, title, monitor, share);
                glfwSetWindowIcon(window, sizeof icons / sizeof icons[0], icons);
            }
    void Window::init(int pWidth, int pHeight, const char* pTitle, GLFWmonitor* pMonitor, GLFWwindow* pShare) {
        height = pHeight;
        width = pWidth;
        title = pTitle;
        monitor = pMonitor;
        share = pShare;
        window = glfwCreateWindow(width, height, title, monitor, share);
    }
    void Window::init(int pWidth, int pHeight, const char* pTitle, GLFWimage* pIcons, GLFWmonitor* pMonitor, GLFWwindow* pShare) {
        height = pHeight;
        width = pWidth;
        title = pTitle;
        monitor = pMonitor;
        share = pShare;
        icons = pIcons;
        window = glfwCreateWindow(width, height, title, monitor, share);
        glfwSetWindowIcon(window, sizeof icons / sizeof icons[0], icons);
    }
    void Window::update() {
        glfwSetWindowPos(window, pos[0], pos[1]);
        glfwSetWindowSize(window, width, height);
        glfwSetWindowTitle(window, title);
    }
    void Window::swapBuffers() {
        glfwSwapBuffers(window);
    }
    void Window::moveTo(int x, int y) {
        pos[0] = x;
        pos[1] = y;
        glfwSetWindowPos(window, pos[0], pos[1]);
    }
    void Window::minimalize() {
        glfwIconifyWindow(window);
    }
    void Window::unMinimalize() {
        glfwRestoreWindow(window);
    }
    void Window::hide() {
        glfwHideWindow(window);
    }
    void Window::show() {
        glfwShowWindow(window);
    }
    void Window::focus() {
        glfwFocusWindow(window);
    }
    void Window::requestAttention() {
        glfwRequestWindowAttention(window);
    }
    void Window::setPositionCallback(GLFWwindowposfun callback) { //! @brief Runs the specified function on change of the position of the window `void window_pos_callback(GLFWwindow* window, int xpos, int ypos) {}`
        glfwSetWindowPosCallback(window, callback);
    }
    void Window::setSizeCallback(GLFWwindowsizefun callback) { //! @brief Runs the specified function on change of the size of the window `void window_size_callback(GLFWwindow* window, int width, int height) {}`
        glfwSetWindowSizeCallback(window, callback);
    }
    void Window::setMinimalizationCallback(GLFWwindowiconifyfun callback) { //! @brief Runs the specified function on the minimalization of the window `void window_iconify_callback(GLFWwindow* window, int iconified) {}`
        glfwSetWindowIconifyCallback(window, callback);
    }
    void Window::setFocusCallback(GLFWwindowfocusfun callback) { //! @brief Runs the specified function on window focus `void window_focus_callback(GLFWwindow* window, int focused) {}`
        glfwSetWindowFocusCallback(window, callback);
    }
    void Window::setCloseCallback(GLFWwindowclosefun callback) { //! @brief Runs the specified function on window closure `void window_close_callback(GLFWwindow* window) {}`
        glfwSetWindowCloseCallback(window, callback);
    }
    void Window::setIconsFromPath(const char** path, int count) {
        GLFWimage* images = new GLFWimage[count];
        for (int i = 0; i < count; i++) {
            images[i].pixels = stbi_load(path[i], &images[i].width, &images[i].height, nullptr, 4);
        }
        icons = images;
        glfwSetWindowIcon(window, count, images);
        for (int i = 0; i < count; i++) {
            if (images[i].pixels) {
                stbi_image_free(images[i].pixels);
            }
        }
        delete[] images;
    }
    void Window::setAttribute(int attrib, int value) {
        glfwSetWindowAttrib(window, attrib, value);
    }
    void Window::setPos(int x, int y) {
        glfwSetWindowPos(window, x, y);
    }
    void Window::setSize(int w, int h) {
        glfwSetWindowSize(window, w, h);
    }
    void Window::setSizeLimits(int minW, int minH, int maxW, int maxH) {
        glfwSetWindowSizeLimits(window, minW, minH, maxW, maxH);
    }
    void Window::setCursor(int cursor) {
        glfwSetInputMode(window, cursorMode, cursor);
    }
    void Window::setCursor(int cursor, int mode) {
        mode = cursor;
        glfwSetInputMode(window, cursorMode, cursor);
    }
    void Window::removeSizeLimits() {
        glfwSetWindowSizeLimits(window, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE);
    }
    void Window::setTitle(const char* t) {
        glfwSetWindowTitle(window, t);
    }
    int Window::getAttribute(int attribute) {
        return glfwGetWindowAttrib(window, attribute);
    }
    int Window::getPosX() {
        int x, y;
        glfwGetWindowPos(window, &x, &y);
        return x;
    }
    int Window::getPosY() {
        int x, y;
        glfwGetWindowPos(window, &x, &y);
        return y;
    }
    int Window::getHeight() {
        int h, w;
        glfwGetWindowSize(window, &h, &w);
        return h;
    }
    int Window::getWidth() {
        int h, w;
        glfwGetWindowSize(window, &h, &w);
        return w;
    }
    const char* Window::getTitle() {
        return glfwGetWindowTitle(window);
    }
    bool Window::shouldClose() {
        return glfwWindowShouldClose(window);
    }
    void Window::destroy() {
        glfwDestroyWindow(window);
    }
    void Window::close() {
        glfwDestroyWindow(window);
    }
    bool Window::WindowInput::WindowInputKey::isReleased(int key) {
        if (glfwGetKey(window.window, key) == GLFW_RELEASE) { return true; }
        return false;
    }
    bool Window::WindowInput::WindowInputKey::isPressed(int key) {
        if (glfwGetKey(window.window, key) == GLFW_PRESS) { return true; }
        return false;
    }
    bool Window::WindowInput::WindowInputKey::isRepeating(int key) {
        if (glfwGetKey(window.window, key) == GLFW_REPEAT) { return true; }
        return false;
    }
    bool Window::WindowInput::WindowInputKey::wasPressed(int key) {
        if (glfwGetKey(window.window, key) == GLFW_PRESS && pressedKeys[key] == false) {
            pressedKeys[key] = true;
            return true;
        }
        checkKeyPress(key);
        return false;
    }
    bool Window::WindowInput::WindowInputKey::wasReleased(int key) {
        if (glfwGetKey(window.window, key) == GLFW_RELEASE && pressedKeys[key] == true) {
            pressedKeys[key] = false;
            return true;
        }
        checkKeyPress(key);
        return false;
    }
    void Window::WindowInput::WindowInputKey::checkKeyPress(int key) {
        if (glfwGetKey(window.window, key) == GLFW_PRESS) {
            pressedKeys[key] = true;
            return;
        }
        pressedKeys[key] = false;
    }

    class Time {
        public:
            static void update();

            static float deltaTime();
            static float unscaledDeltaTime();
            static float elapsedTime();
            static float fps();

            inline static float timeRate();
            static void setTimeRate(float scale);

        private:
            inline static double lastTime = 0.0;
            inline static double startTime = 0.0;
            inline static float delta = 0.0f;
            inline static float unscaledDelta = 0.0f;
            inline static float timeRateVar = 1.0f;
            inline static float currentFps = 0.0f;
            inline static int frameCount = 0;
            inline static double fpsTimer = 0.0;
    };
    void Time::update() {
        double now = glfwGetTime();
        if (startTime == 0.0) {
            startTime = now;
            lastTime = now;
        }
        unscaledDelta = static_cast<float>(now - lastTime);
        lastTime = now;
        delta = unscaledDelta * timeRateVar; // Apply game speed multiplier
        frameCount++; // FPS counter
        fpsTimer += unscaledDelta;
        if (now - fpsTimer >= 1.0) {
            currentFps = static_cast<float>(frameCount);
            frameCount = 0;
            fpsTimer = now;
        }
    }
    float Time::deltaTime() {
        return delta;
    }
    float Time::unscaledDeltaTime() {
        return unscaledDelta;
    }
    float Time::elapsedTime() {
        return static_cast<float>(glfwGetTime() - startTime);
    }
    float Time::fps() {
        return currentFps;
    }
    float Time::timeRate() {
        return timeRateVar;
    }
    void Time::setTimeRate(float value) {
        timeRateVar = std::max(value, 0.0f);
    }

    class Shader {
        public:
            GLuint ID;
            Shader(const char* vertexPath, const char* fragmentPath);
            void use();
            void setInt(const std::string& name, int value) const;
            void setMat4(const std::string& name, const glm::mat4& matrix) const;
    };
    Shader::Shader(const char* vertexPath, const char* fragmentPath) {
        std::ifstream vFile(vertexPath);
        std::ifstream fFile(fragmentPath);
        std::stringstream vStream;
        std::stringstream fStream;

        vStream << vFile.rdbuf();
        fStream << fFile.rdbuf();

        std::string vString = vStream.str();
        std::string fString = fStream.str();
        const char* vCode = vString.c_str();
        const char* fCode = fString.c_str();

        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vCode, nullptr);
        glCompileShader(vertex);

        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fCode, nullptr);
        glCompileShader(fragment);

        ID = glCreateProgram();

        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    void Shader::use() {
        glUseProgram(ID);
    }
    void Shader::setInt(const std::string& name, int value) const {
        glUniform1i( glGetUniformLocation(ID, name.c_str()), value );
    }
    void Shader::setMat4(const std::string& name, const glm::mat4& matrix) const {
        glUniformMatrix4fv(
            glGetUniformLocation(ID, name.c_str()),
            1,
            GL_FALSE,
            glm::value_ptr(matrix)
        );
    }

    enum class TextureFlip {
        None,
        X,
        Y,
        XY
    };
    enum class TextureRotation {
        Deg0,
        Deg90,
        Deg180,
        Deg270
    };
    class Texture {
        private:
            inline static Texture* currentlyBound = nullptr;
            GLuint textureID;
            int width;
            int height;
            int channels;
        public:
            Texture();
            Texture(const char* path);
            Texture(const char** path);
            Texture(const Texture&) = delete;
            Texture& operator=(const Texture&) = delete;
            Texture(Texture&& other) noexcept;
            Texture& operator=(Texture&& other) noexcept;
            ~Texture();
            bool load(const std::string& path);
            //void setID(GLuint id);
            void bind(unsigned int slot = 0) const;
            void unbind() const;
            void flip(TextureFlip flip);
            void rotate(TextureRotation rotation);
            GLuint getID() const;
            int getWidth() const;
            int getHeight() const;
            TextureFlip getFlip() const;
            TextureRotation getRotation() const;
            inline static int textureBinds = 0;
    };
    Texture::Texture() {
        textureID = 0;
        width = 0;
        height = 0;
        channels = 0;
        // flipState = TextureFlip::None;
        // rotationState = TextureRotation::Deg0;
    }
    Texture::Texture(const char* path) : Texture() {
        load(path);
    }
    Texture::Texture(const char** path) : Texture() {
        if (path && *path) load(*path);
    }
    Texture::Texture(Texture&& other) noexcept {
        textureID = other.textureID;
        width = other.width;
        height = other.height;
        channels = other.channels;
        // flipState = other.flipState;
        // rotationState = other.rotationState;

        other.textureID = 0;
        other.width = 0;
        other.height = 0;
        other.channels = 0;
    }
    Texture& Texture::operator=(Texture&& other) noexcept {
        if (this != &other) {
            if (textureID) glDeleteTextures(1, &textureID);

            textureID = other.textureID;
            width = other.width;
            height = other.height;
            channels = other.channels;
            // flipState = other.flipState;
            // rotationState = other.rotationState;

            other.textureID = 0;
            other.width = 0;
            other.height = 0;
            other.channels = 0;
        }
        return *this;
    }
    Texture::~Texture() {
        if(textureID) glDeleteTextures(1, &textureID);
    }
    bool Texture::load(const std::string& path) {
        if (textureID) {
            glDeleteTextures(1, &textureID);
            textureID = 0;
        }
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data =
            stbi_load(
                path.c_str(),
                &width,
                &height,
                &channels,
                0
            );
        if(!data) return false;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_S,
            GL_REPEAT
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_T,
            GL_REPEAT
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            GL_NEAREST
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            GL_NEAREST
        );

        GLenum format = GL_RGB;

        if(channels == 1)       format = GL_RED;
        else if(channels == 3)  format = GL_RGB;
        else if(channels == 4)  format = GL_RGBA;

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            format,
            width,
            height,
            0,
            format,
            GL_UNSIGNED_BYTE,
            data
        );

        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        return true;
    }
    // void Texture::setID(GLuint id) {
    //     if (textureID && textureID != id) glDeleteTextures(1, &textureID);
    //     textureID = id;
    // }
    void Texture::bind(unsigned int slot) const {
        if (currentlyBound == this) return;
        textureBinds++;
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, textureID);
        currentlyBound = const_cast<Texture*>(this);
    }
    void Texture::unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // void Texture::flip(TextureFlip flip) {
    //     flipState = flip;
    // }
    // void Texture::rotate(TextureRotation rotation) {
    //     rotationState = rotation;
    // }
    GLuint Texture::getID() const {
        return textureID;
    }
    int Texture::getWidth() const {
        return width;
    }
    int Texture::getHeight() const {
        return height;
    }
    // TextureFlip Texture::getFlip() const {
    //     return flipState;
    // }
    // TextureRotation Texture::getRotation() const {
    //     return rotationState;
    // }

    class TextureManager {
        public:
            //static Texture& get(const std::string& path);
            static std::shared_ptr<Texture> get(const std::string& path);
            //static Texture* get(const std::string& path);
        private:
            inline static std::unordered_map<std::string, std::weak_ptr<Texture>> textures;
    };
    // Texture& TextureManager::get(const std::string& path) {
    //     auto it = textures.find(path);
    //     if (it != textures.end())
    //         return it->second;
    //     auto result = textures.emplace(
    //         path,
    //         Texture(path.c_str())
    //     );
    //     return result.first->second;
    // }
    //Texture* TextureManager::get(const std::string& path) {
    std::shared_ptr<Texture> TextureManager::get(const std::string& path) {
        auto foundTex = textures.find(path);
        if (foundTex != textures.end())
            if (auto texture = foundTex->second.lock()) return texture;
        auto texture = std::make_shared<Texture>();
        if (!texture->load(path)) {
            Console::error("Failed to load texture %s", path.c_str());
            return nullptr;
        }
        textures[path] = texture;
        return texture;
    }

    class Sprite;

    struct SpriteRenderData {
        std::shared_ptr<Texture> texture;
        //Texture* texture = nullptr;

        float u1 = 0.0f;
        float v1 = 0.0f;
        float u2 = 1.0f;
        float v2 = 1.0f;
    };
    
    class BatchRenderer {
        public:
            static void init();
            static void begin();
            static void submit(Sprite& sprite);
            static void end(Shader& shader);
            static void add(Texture* texture, float x, float y, float w, float h, float rotation, TextureFlip flip);
            static void flush();
        private:
            struct Vertex {
                glm::vec2 position;
                glm::vec2 texCoord;
            };

            inline static std::vector<Vertex> vertices;
            inline static std::vector<unsigned int> indices;

            inline static GLuint VAO = 0;
            inline static GLuint VBO = 0;
            inline static GLuint EBO = 0;

            // inline static std::shared_ptr<Texture> currentTexture = nullptr;
            inline static Texture* currentTexture = nullptr;
    };

    class Sprite {
        public:
            Sprite();
            Sprite(const char* path, Shader* shader = nullptr, unsigned int textureSlot = 0);
            // Sprite(const char** path, Shader* shader = nullptr, unsigned int textureSlot = 0);
            Sprite(const Sprite&) = delete;
            Sprite& operator=(const Sprite&) = delete;
            Sprite(Sprite&& other) noexcept = default;
            Sprite& operator=(Sprite&& other) noexcept = default;
            ~Sprite();

            bool load(const char* path);
            void setShader(Shader* shader);
            //void setTextureID(GLuint id);
            void setTextureSlot(unsigned int slot);
            void position(float px, float py);
            void size(float pw, float ph);
            void rotate(TextureRotation rotation);
            void rotate(float degrees);
            void setRotation(float degrees);
            void flip(TextureFlip flip);
            void draw();
            // void draw(Shader& shader);
            //void draw(BatchRenderer& renderer);
            void submit(BatchRenderer& renderer);
            float getSpriteWidth() const;
            float getSpriteHeight() const;
            float getSpritePosX() const;
            float getSpritePosY() const;
            int getTextureHeight() const;
            int getTextureWidth() const;
            int getTextureHeight(int frame) const;
            int getTextureWidth(int frame) const;
            TextureFlip getFlip() const;
            float getRotation() const;
            void setTexture(std::shared_ptr<Texture>& tex);
            std::shared_ptr<Texture> getTextureShared() const;
            Texture* getTexture() const;
            inline static int drawCalls = 0;
            inline static int textureBinds = 0;
        private:
            SpriteRenderData renderData;
            std::shared_ptr<Texture> textureOwner;
            Shader* defaultShader;
            unsigned int textureSlot;
            float x, y;
            float w, h;
            float rotationDegrees;
            TextureFlip flipState;
            static GLuint VAO, VBO, EBO;
            static bool initialized;
            static void initQuad();
            bool hasTexture;
            inline static int lastTextureSlot = -1;
            // TextureFlip flipState;
            // TextureRotation rotationState;
    };
    void BatchRenderer::init() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(
            GL_ARRAY_BUFFER,
            10000 * sizeof(Vertex),
            nullptr,
            GL_DYNAMIC_DRAW
        );

        glVertexAttribPointer(
            0,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void*)0
        );

        glEnableVertexAttribArray(0);

        glVertexAttribPointer(
            1,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void*)offsetof(Vertex, texCoord)
        );
        glEnableVertexAttribArray(1);
    }
    void BatchRenderer::begin() {
        vertices.clear();
        indices.clear();
    }
    void BatchRenderer::submit(Sprite& sprite) {
        if (!sprite.getTexture()) {
            Console::error("TExture load someshit TODO");
            return;
        }
        if (currentTexture && currentTexture != sprite.getTexture()) {
            // flush later
        }
        currentTexture = sprite.getTexture();
        float x = sprite.getSpritePosX();
        float y = sprite.getSpritePosY();
        float w = sprite.getSpriteWidth();
        float h = sprite.getSpriteHeight();

        unsigned int start = vertices.size();

        vertices.push_back({{x - w / 2, y - h / 2}, {0, 0}});
        vertices.push_back({{x + w / 2, y - h / 2}, {1, 0}});
        vertices.push_back({{x + w / 2, y + h / 2}, {1, 1}});
        vertices.push_back({{x - w / 2, y + h / 2}, {0, 1}});

        indices.push_back(start+0);
        indices.push_back(start+1);
        indices.push_back(start+2);

        indices.push_back(start+2);
        indices.push_back(start+3);
        indices.push_back(start+0);
    }
    void BatchRenderer::end(Shader& shader) {
        shader.use();
        if (currentTexture) {
            currentTexture->bind(0);
            shader.setInt("tex", 0);
        }
        flush();
        // glBindBuffer(GL_ARRAY_BUFFER,VBO);

        // glBufferSubData(
        //     GL_ARRAY_BUFFER,
        //     0,
        //     vertices.size()*sizeof(Vertex),
        //     vertices.data()
        // );

        // glBindVertexArray(VAO);

        // glDrawElements(
        //     GL_TRIANGLES,
        //     indices.size(),
        //     GL_UNSIGNED_INT,
        //     0
        // );
    }
    void BatchRenderer::add(Texture* texture, float x, float y, float w, float h, float rotation, TextureFlip flip) {
        if (!texture)
            return;
        // Flush if the texture changes
        // Console::trace(
        //     "Batch add texture=%p",
        //     texture
        // );
        if (currentTexture && currentTexture != texture) flush();
        currentTexture = texture;
        float left   = -w * 0.5f;
        float right  =  w * 0.5f;
        float bottom = -h * 0.5f;
        float top    =  h * 0.5f;
        glm::vec2 corners[4] = {
            { left,  bottom },
            { right, bottom },
            { right, top    },
            { left,  top    }
        };
        if (rotation != 0.0f) {
            float r = glm::radians(rotation);
            float c = cos(r);
            float s = sin(r);
            for (auto& corner : corners) {
                float px = corner.x;
                float py = corner.y;
                corner.x = px * c - py * s;
                corner.y = px * s + py * c;
            }
        }
        for (auto& corner : corners) {
            corner.x += x;
            corner.y += y;
        }
        glm::vec2 uv[4] = {
            {0,0},
            {1,0},
            {1,1},
            {0,1}
        };
        switch (flip) {
            case TextureFlip::X:
                std::swap(uv[0].x, uv[1].x);
                std::swap(uv[3].x, uv[2].x);
                break;
            case TextureFlip::Y:
                std::swap(uv[0].y, uv[3].y);
                std::swap(uv[1].y, uv[2].y);
                break;
            case TextureFlip::XY:
                std::swap(uv[0], uv[2]);
                std::swap(uv[1], uv[3]);
                break;
            default:
                break;
        }
        unsigned int start = static_cast<unsigned int>(vertices.size());

        vertices.push_back({ corners[0], uv[0] });
        vertices.push_back({ corners[1], uv[1] });
        vertices.push_back({ corners[2], uv[2] });
        vertices.push_back({ corners[3], uv[3] });
        indices.push_back(start + 0);
        indices.push_back(start + 1);
        indices.push_back(start + 2);
        indices.push_back(start + 2);
        indices.push_back(start + 3);
        indices.push_back(start + 0);
        // Console::trace(
        //     "Batch vertices: %d | indices: %d",
        //     vertices.size(),
        //     indices.size()
        // );
    }
    void BatchRenderer::flush() {
        // Console::trace(
        //     "FLUSH called: vertices=%d indices=%d texture=%p",
        //     vertices.size(),
        //     indices.size(),
        //     currentTexture
        // );
        if (vertices.empty())
            return;

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(
            GL_ARRAY_BUFFER,
            0,
            vertices.size() * sizeof(Vertex),
            vertices.data()
        );
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferSubData(
            GL_ELEMENT_ARRAY_BUFFER,
            0,
            indices.size() * sizeof(unsigned int),
            indices.data()
        );
        glBindVertexArray(VAO);
        glDrawElements(
            GL_TRIANGLES,
            static_cast<GLsizei>(indices.size()),
            GL_UNSIGNED_INT,
            nullptr
        );
        vertices.clear();
        indices.clear();
        currentTexture = nullptr;
    }

    Sprite::Sprite() {
        if (!initialized) initQuad();
        //renderData.texture = nullptr;//std::make_shared<Texture>();
        hasTexture = true;
        defaultShader = nullptr;
        textureSlot = 0;
        x = y = 0.0f;
        w = h = 1.0f;
        rotationDegrees = 0.0f;
        flipState = TextureFlip::None;
    }
    Sprite::~Sprite() = default;
    Sprite::Sprite(const char* path, Shader* shader, unsigned int slot) : Sprite() {
        defaultShader = shader;
        textureSlot = slot;
        load(path);
    }
    // Sprite::Sprite(const char** path, Shader* shader, unsigned int slot) : Sprite() {
    //     defaultShader = shader;
    //     textureSlot = slot;
    //     if (path && *path) load(*path);
    // }
    // Sprite::Sprite(Sprite&& other) noexcept : texture(std::move(other.texture)) {
    //     texture = std::move(other.texture);
    //     hasTexture = other.hasTexture;
    //     defaultShader = other.defaultShader;
    //     textureSlot = other.textureSlot;
    //     x = other.x;
    //     y = other.y;
    //     w = other.w;
    //     h = other.h;
    //     rotationDegrees = other.rotationDegrees;
    //     flipState = other.flipState;
    // }
    // Sprite& Sprite::operator=(Sprite&& other) noexcept {
    //     if (this != &other) {
    //         texture = other.texture;
    //         hasTexture = other.hasTexture;
    //         defaultShader = other.defaultShader;
    //         textureSlot = other.textureSlot;
    //         x = other.x;
    //         y = other.y;
    //         w = other.w;
    //         h = other.h;
    //         rotationDegrees = other.rotationDegrees;
    //         flipState = other.flipState;
    //     }
    //     return *this;
    // }
    // bool Sprite::load(const char* path) {
    //     texture = TextureManager::get(path);
    //     if (!texture) {
    //         Console::error("Failed to load sprite %s", path);
    //         return false;
    //     }
    //     Console::trace("Sprite %s loaded with ID %d", path, texture->getID());
    //     return true;
    // }
    bool Sprite::load(const char* path) {
        textureOwner = TextureManager::get(path);
        if (!textureOwner) {
            Console::error("Failed to load sprite %s", path);
            return false;
        }
        // Console::trace(
        //     "Loaded %s texture ID: %d",
        //     path,
        //     textureOwner->getID()
        // );
        renderData.texture = textureOwner;
        renderData.u1 = 0.0f;
        renderData.v1 = 0.0f;
        renderData.u2 = 1.0f;
        renderData.v2 = 1.0f;
        return true;
    }
    /*bool Sprite::load(const char* path) {
        if (!texture)
            texture = std::make_shared<Texture>();
        return texture->load(path);
    }*/
    /*bool Sprite::load(const char* path) {
        texture = TextureManager::get(path);
        return texture != nullptr;
    }*/
    void Sprite::setShader(Shader* shader) {
        defaultShader = shader;
    }
    // void Sprite::setTextureID(GLuint id) {
    //     texture->setID(id);
    // }
    void Sprite::setTextureSlot(unsigned int slot) {
        textureSlot = slot;
    }
    void Sprite::position(float px, float py) {
        x = px;
        y = py;
    }
    void Sprite::size(float pw, float ph) {
        w = pw;
        h = ph;
    }
    void Sprite::rotate(TextureRotation rotation) {
        switch (rotation) {
            case TextureRotation::Deg0:   rotationDegrees = 0.0f; break;
            case TextureRotation::Deg90:  rotationDegrees = 90.0f; break;
            case TextureRotation::Deg180: rotationDegrees = 180.0f; break;
            case TextureRotation::Deg270: rotationDegrees = 270.0f; break;
        }
    }
    void Sprite::rotate(float degrees) {
        rotationDegrees += degrees;
    }
    void Sprite::setRotation(float degrees) {
        rotationDegrees = degrees;
    }
    void Sprite::flip(TextureFlip flip) {
        flipState = flip;
    }
    /*void Sprite::draw() {
        if (defaultShader) draw(*defaultShader);
    }
    void Sprite::draw(Shader& shader) {
        if (!renderData.texture) return;
        glm::mat4 model = glm::mat4(1.0f);
        float drawW = w;
        float drawH = h;

        if (flipState == TextureFlip::X || flipState == TextureFlip::XY) drawW *= -1.0f;
        if (flipState == TextureFlip::Y || flipState == TextureFlip::XY) drawH *= -1.0f;

        model = glm::translate(model, glm::vec3(x, y, 0.0f));
        model = glm::rotate(model, glm::radians(rotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(drawW, drawH, 1.0f));

        shader.setMat4("model", model);

        renderData.texture->bind(textureSlot);
        // shader.setInt("tex", textureSlot);
        if (lastTextureSlot != textureSlot) {
            shader.setInt("tex", textureSlot);
            lastTextureSlot = textureSlot;
        }

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        drawCalls++;
    }*/
    //void Sprite::draw(BatchRenderer& renderer) {
    void Sprite::draw() {
        // Console::trace(
        //     "Sprite draw texture=%p",
        //     renderData.texture.get()
        // );
        BatchRenderer::add(
            renderData.texture.get(),
            x,
            y,
            w,
            h,
            rotationDegrees,
            flipState
        );
    }
    void Sprite::submit(BatchRenderer& renderer) {
        renderer.add(
            renderData.texture.get(),
            x, y,
            w, h,
            rotationDegrees,
            flipState
        );
    }
    float Sprite::getSpriteWidth() const {
        return w;
    }
    float Sprite::getSpriteHeight() const {
        return h;
    }
    float Sprite::getSpritePosX() const {
        return x;
    }
    float Sprite::getSpritePosY() const {
        return y;
    }
    int Sprite::getTextureHeight() const {
        return renderData.texture ? renderData.texture->getHeight() : 0;
    }
    int Sprite::getTextureWidth() const {
        return renderData.texture ? renderData.texture->getWidth() : 0;
    }
    int Sprite::getTextureHeight(int frame) const {
        return renderData.texture->getHeight();
    }
    int Sprite::getTextureWidth(int frame) const {
        return renderData.texture->getWidth();
    }
    TextureFlip Sprite::getFlip() const {
        return flipState;
    }
    float Sprite::getRotation() const {
        return rotationDegrees;
    }
    void Sprite::setTexture(std::shared_ptr<Texture>& tex) {
        renderData.texture = std::move(tex);
        // hasTexture = false;
    }
    // const std::shared_ptr<Texture> Sprite::getTexture() const {
    //     return renderData.texture;
    // }
    Texture* Sprite::getTexture() const {
        return renderData.texture.get();
    }
    void Sprite::initQuad() {
        float vertices[] = {
            // pos         // tex
            -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.0f, 1.0f
        };

        unsigned int indices[] = {
            0,1,2,
            2,3,0
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

        initialized = true;
    }
    GLuint Sprite::VAO = 0;
    GLuint Sprite::VBO = 0;
    GLuint Sprite::EBO = 0;
    bool Sprite::initialized = false;

    class AnimatedSprite {
        public:
            AnimatedSprite();
            AnimatedSprite(const char** paths, int count, Shader* shader = nullptr, float defaultFrameTime = 0.1f, const float* frameTimes = nullptr);
            AnimatedSprite(std::initializer_list<const char*> paths, int count, Shader* shader = nullptr, float defaultFrameTime = 0.1f, std::initializer_list<float> frameTimes = {});
            AnimatedSprite(Sprite* sprites, int count, Shader* shader = nullptr, float defaultFrameTime = 0.1f, const float* frameTimes = nullptr);
            void load(const char** paths, int count, Shader* shader = nullptr, float defaultFrameTime = 0.1f, const float* frameTimes = nullptr);
            void load(std::initializer_list<const char*> paths, int count, Shader* shader = nullptr, float defaultFrameTime = 0.1f, std::initializer_list<float> frameTimes = {});
            void load(Sprite* sprites, int count, Shader* shader = nullptr, float defaultFrameTime = 0.1f, const float* frameTimes = nullptr);
            void loadFromPath(const char* path, Shader* shader);
            void setShader(Shader* shader);
            void position(float px, float py);
            void size(float pw, float ph);
            void rotate(TextureRotation rotation);
            void rotate(float degrees);
            void setRotation(float degrees);
            void flip(TextureFlip flip);
            void setFrameTime(float seconds);
            void setFrameTime(int frame, float seconds);
            void setFrame(int frame);
            int getFrame() const;
            int getFrameCount() const;
            Sprite& getSprite(int frame);
            void draw();
            //void draw(Shader& shader);
            void draw(BatchRenderer& renderer);
            AnimatedSprite(const AnimatedSprite&) = delete;
            AnimatedSprite& operator=(const AnimatedSprite&) = delete;

            AnimatedSprite(AnimatedSprite&&) noexcept = default;
            AnimatedSprite& operator=(AnimatedSprite&&) noexcept = default;
        private:
            std::vector<Sprite> frames;
            std::vector<float> frameTimes;
            int activeFrame;
            double lastFrameChange;
            Shader* defaultShader;
            float defaultFrameTime;
            void updateFrame();
            void syncFrame(Sprite& frame);
            float x, y;
            float w, h;
            float rotationDegrees;
            TextureFlip flipState;
    };
    AnimatedSprite::AnimatedSprite() {
        activeFrame = 0;
        lastFrameChange = glfwGetTime();
        defaultShader = nullptr;
        defaultFrameTime = 0.1f;
        x = y = 0.0f;
        w = h = 1.0f;
        rotationDegrees = 0.0f;
        flipState = TextureFlip::None;
    }
    AnimatedSprite::AnimatedSprite(const char** paths, int count, Shader* shader, float pDefaultFrameTime, const float* pFrameTimes) : AnimatedSprite() {
        load(paths, count, shader, pDefaultFrameTime, pFrameTimes);
    }
    AnimatedSprite::AnimatedSprite(std::initializer_list<const char*> paths, int count, Shader* shader, float pDefaultFrameTime, std::initializer_list<float> pFrameTimes) : AnimatedSprite() {
        load(paths, count, shader, pDefaultFrameTime, pFrameTimes);
    }
    AnimatedSprite::AnimatedSprite(Sprite* sprites, int count, Shader* shader, float pDefaultFrameTime, const float* pFrameTimes) : AnimatedSprite() {
        load(sprites, count, shader, pDefaultFrameTime, pFrameTimes);
    }
    void AnimatedSprite::load(const char** paths, int count, Shader* shader, float pDefaultFrameTime, const float* pFrameTimes) {
        frames.clear();
        frameTimes.clear();
        defaultShader = shader;
        defaultFrameTime = pDefaultFrameTime;
        activeFrame = 0;
        lastFrameChange = glfwGetTime();

        for (int i = 0; i < count; i++) {
            frames.emplace_back(paths[i], shader);
            frameTimes.push_back(pFrameTimes && pFrameTimes[i] >= 0.0f ? pFrameTimes[i] : defaultFrameTime);
            syncFrame(frames.back());
        }
    }
    void AnimatedSprite::load(std::initializer_list<const char*> paths, int count, Shader* shader, float pDefaultFrameTime, std::initializer_list<float> pFrameTimes) {
        frames.clear();
        frameTimes.clear();
        defaultShader = shader;
        defaultFrameTime = pDefaultFrameTime;
        activeFrame = 0;
        lastFrameChange = glfwGetTime();

        int i = 0;
        auto frameTime = pFrameTimes.begin();
        for (const char* path : paths) {
            if (i >= count) break;

            frames.emplace_back(path, shader);
            if (frameTime != pFrameTimes.end()) {
                float seconds = *frameTime++;
                frameTimes.push_back(seconds >= 0.0f ? seconds : defaultFrameTime);
            } else {
                frameTimes.push_back(defaultFrameTime);
            }
            syncFrame(frames.back());
            i++;
        }
    }
    void AnimatedSprite::load(Sprite* sprites, int count, Shader* shader, float pDefaultFrameTime, const float* pFrameTimes) {
        frames.clear();
        frameTimes.clear();

        defaultShader = shader;
        defaultFrameTime = pDefaultFrameTime;
        activeFrame = 0;
        lastFrameChange = glfwGetTime();

        for (int i = 0; i < count; i++) {
            frames.push_back(std::move(sprites[i]));

            frameTimes.push_back(
                (pFrameTimes && pFrameTimes[i] >= 0.0f)
                    ? pFrameTimes[i]
                    : defaultFrameTime
            );

            syncFrame(frames.back());
        }
    }
    void AnimatedSprite::loadFromPath(const char* path, Shader* shader) {
        // TODO: fix rotation and flipping, remove hardcoded path to textures
        std::string pathString = "data/assets/";
        nlohmann::json animJson = JSON::ParseJSONFile(path);
        //std::cout << animJson << "\n\n" << animJson["frames"] << "\n\n";
        int framesCount = static_cast<int>(animJson["frames"].size());
        Sprite* framesParam = new Sprite[framesCount];
        float* timesParam = new float[framesCount];
        float defaultTime = animJson["frameTime"].get<float>();
        //std::cout << framesCount << "  test\n";
        for (int i = 0; i < framesCount; i++) {
            //std::cout << (pathString + animJson["frames"][i]["path"].get<std::string>()).c_str() << "\n";
            //std::cout << animJson["frames"][i] << "\n\n";
            //std::cout << "testtestettrtewrgwhe\n";
            //framesParam[i] = Sprite();
            framesParam[i].load((pathString + animJson["frames"][i]["path"].get<std::string>()).c_str());
            framesParam[i].setRotation(animJson["frames"][i].value("rotation", 0.0));
            bool flipX = animJson["frames"][i].value("flipX", false);
            bool flipY = animJson["frames"][i].value("flipY", false);
            //std::cout << "X: " << flipX << ", Y: " << flipY << "; rot: " << animJson["frames"][i].value("rotation", 0.0) << ";\t";
            if (!flipX && !flipY) {
                //std::cout << "None\n";
                framesParam[i].flip(TextureFlip::None);
            } else if (flipX && !flipY) {
                //std::cout << "X\n";
                framesParam[i].flip(TextureFlip::X);
            } else if (!flipX && flipY) {
                //std::cout << "Y\n";
                framesParam[i].flip(TextureFlip::Y);
            } else if (flipX && flipY) {
                //std::cout << "XY\n";
                framesParam[i].flip(TextureFlip::XY);
            }
            timesParam[i] = animJson["frames"][i].value("time", defaultTime);
        }
        load(framesParam, framesCount, shader, defaultTime, timesParam);
        delete[] framesParam;
        delete[] timesParam;
    }
    void AnimatedSprite::setShader(Shader* shader) {
        defaultShader = shader;
        for (int i = 0; i < frames.size(); i++) frames[i].setShader(shader);
    }
    void AnimatedSprite::position(float px, float py) {
        x = px;
        y = py;
        for (int i = 0; i < frames.size(); i++) frames[i].position(px, py);
    }
    void AnimatedSprite::size(float pw, float ph) {
        w = pw;
        h = ph;
        for (int i = 0; i < frames.size(); i++) frames[i].size(pw, ph);
    }
    void AnimatedSprite::rotate(TextureRotation rotation) {
        switch (rotation) {
            case TextureRotation::Deg0:   rotationDegrees = 0.0f; break;
            case TextureRotation::Deg90:  rotationDegrees = 90.0f; break;
            case TextureRotation::Deg180: rotationDegrees = 180.0f; break;
            case TextureRotation::Deg270: rotationDegrees = 270.0f; break;
        }
        for (int i = 0; i < frames.size(); i++) frames[i].setRotation(rotationDegrees);
    }
    void AnimatedSprite::rotate(float degrees) {
        rotationDegrees += degrees;
        for (int i = 0; i < frames.size(); i++) frames[i].rotate(degrees);
    }
    void AnimatedSprite::setRotation(float degrees) {
        rotationDegrees = degrees;
        for (int i = 0; i < frames.size(); i++) frames[i].setRotation(degrees);
    }
    void AnimatedSprite::flip(TextureFlip flip) {
        flipState = flip;
        for (int i = 0; i < frames.size(); i++) frames[i].flip(flip);
    }
    void AnimatedSprite::setFrameTime(float seconds) {
        defaultFrameTime = seconds;
        for (int i = 0; i < frameTimes.size(); i++) frameTimes[i] = seconds;
    }
    void AnimatedSprite::setFrameTime(int frame, float seconds) {
        if (frame >= 0 && frame < frameTimes.size()) frameTimes[frame] = seconds;
    }
    void AnimatedSprite::setFrame(int frame) {
        if (frame < 0 || frame >= frames.size()) return;
        activeFrame = frame;
        lastFrameChange = glfwGetTime();
    }
    int AnimatedSprite::getFrame() const {
        return activeFrame;
    }
    int AnimatedSprite::getFrameCount() const {
        return (int)frames.size();
    }
    Sprite& AnimatedSprite::getSprite(int frame) {
        return frames[frame];
    }
    void AnimatedSprite::draw() {
        if (frames.empty()) return;
        updateFrame();
        frames[activeFrame].draw();
        // Sprite& lSprite = frames[activeFrame];
        // BatchRenderer::add(
        //     lSprite.getTexture(),
        //     lSprite.getSpritePosX(),
        //     lSprite.getSpritePosY(),
        //     lSprite.getSpriteWidth(),
        //     lSprite.getSpriteHeight(),
        //     lSprite.getRotation(),
        //     lSprite.getFlip()
        // );
    }
    void AnimatedSprite::draw(BatchRenderer& renderer) {
        if (frames.empty()) return;
        updateFrame();
        frames[activeFrame].submit(renderer);
    }
    void AnimatedSprite::updateFrame() {
        if (frames.size() <= 1) return;

        double now = glfwGetTime();
        float currentFrameTime = frameTimes.empty() ? defaultFrameTime : frameTimes[activeFrame];
        if (now - lastFrameChange >= currentFrameTime) {
            activeFrame = (activeFrame + 1) % frames.size();
            lastFrameChange = now;
        }
    }
    void AnimatedSprite::syncFrame(Sprite& frame) {
        frame.position(x, y);
        frame.size(w, h);
        frame.setRotation(rotationDegrees);
        frame.flip(flipState);
        frame.setShader(defaultShader);
    }

    class Sound {};

    struct MusicSection {
        const char* id = "";
        float start = 0;
        float lenght = 1;
    };
    class Music {
        public:
            MusicSection* load(const char* path);
            void nextSection();
            void previousSection();
            int getActiveSection();
        private:
            int section = 0;
            MusicSection* sections;
    };
    MusicSection* Music::load(const char* path) {
        nlohmann::json json;
        MusicSection* result;
        std::string ids = " ";
        try {
            json = {}; //load from path
        } catch (std::exception&) {}
        for (int i = 0; i < json["sections"].size(); i++) {
            if (!json["sections"][i].contains("id")) {
                //throw exception
                return NULL;
            }
            if (!json["sections"][i].contains("start")) {
                //throw exception
                return NULL;
            }
            if (ids.find(" " + json["sections"][i]["id"].get<std::string>() + " ") != std::string::npos) {
                //throw exception
                return NULL;
            }
            result[i] = {
                json["sections"][i]["id"].get<std::string>().c_str(),
                json["sections"][i].value("start", 0.0f),
                json["sections"][i].contains("length")
                    ? json["sections"][i]["length"].get<float>()
                    : i + 1 < json["sections"].size()
                        ? json["sections"][i + 1]["start"].get<float>() - json["sections"][i]["start"].get<float>()
                        : json["length"].get<float>()
            };
            ids.append(json["sections"][i]["id"].get<std::string>() + " ");
        }
        return result;
    }

    struct ObjectIdentifier {
        const char* Namespace;
        const char* Id;
    };


}

//Mistical::Window testWindow;
// void test() {
//     testWindow.init(1, 2, "title");
//     testWindow.init();
// }
    // void setIconsFromPath(const char** path) {
    //     GLFWimage* images;
    //     for (int i = 0; i < sizeof path / sizeof path[0]; i++) {
    //         images[i].pixels = stbi_load(path[i], &images[i].width, &images[i].height, 0, 4);
    //     }
    //     icons = images;
    //     glfwSetWindowIcon(window, sizeof icons / sizeof icons[0], icons);
    //     for (int i = 0; i < sizeof path / sizeof path[0]; i++) {
    //         stbi_image_free(images[i].pixels);
    //     }
    // }
enum timeUnits {
    nanoSeconds,
    microSeconds,
    miliSeconds,
    seconds,
    minutes,
    hours
};
void sleep(unsigned int time, timeUnits unit = miliSeconds) {
    switch (unit) {
        case nanoSeconds:   std::this_thread::sleep_for(std::chrono::nanoseconds(time));
        case microSeconds:  std::this_thread::sleep_for(std::chrono::microseconds(time));
        case miliSeconds:   std::this_thread::sleep_for(std::chrono::milliseconds(time));
        case seconds:       std::this_thread::sleep_for(std::chrono::seconds(time));
        case minutes:       std::this_thread::sleep_for(std::chrono::minutes(time));
        case hours:         std::this_thread::sleep_for(std::chrono::hours(time));
    }
}


void miniCb(GLFWwindow* window, int iconified) {
    if (iconified == GLFW_TRUE) {
        glfwRequestWindowAttention(window);
    }
}

const char* keyStrings[349] = {
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "GLFW_KEY_SPACE",
    "",
    "",
    "",
    "",
    "",
    "",
    "GLFW_KEY_APOSTROPHE",           /* ' */
    "",
    "",
    "",
    "",
    "GLFW_KEY_COMMA",                /* , */
    "GLFW_KEY_MINUS",                /* - */
    "GLFW_KEY_PERIOD",               /* . */
    "GLFW_KEY_SLASH",                /* / */
    "GLFW_KEY_0",
    "GLFW_KEY_1",
    "GLFW_KEY_2",
    "GLFW_KEY_3",
    "GLFW_KEY_4",
    "GLFW_KEY_5",
    "GLFW_KEY_6",
    "GLFW_KEY_7",
    "GLFW_KEY_8",
    "GLFW_KEY_9",
    "",
    "GLFW_KEY_SEMICOLON",            /* ; */
    "",
    "GLFW_KEY_EQUAL",                /* = */
    "",
    "",
    "",
    "GLFW_KEY_A",
    "GLFW_KEY_B",
    "GLFW_KEY_C",
    "GLFW_KEY_D",
    "GLFW_KEY_E",
    "GLFW_KEY_F",
    "GLFW_KEY_G",
    "GLFW_KEY_H",
    "GLFW_KEY_I",
    "GLFW_KEY_J",
    "GLFW_KEY_K",
    "GLFW_KEY_L",
    "GLFW_KEY_M",
    "GLFW_KEY_N",
    "GLFW_KEY_O",
    "GLFW_KEY_P",
    "GLFW_KEY_Q",
    "GLFW_KEY_R",
    "GLFW_KEY_S",
    "GLFW_KEY_T",
    "GLFW_KEY_U",
    "GLFW_KEY_V",
    "GLFW_KEY_W",
    "GLFW_KEY_X",
    "GLFW_KEY_Y",
    "GLFW_KEY_Z",
    "GLFW_KEY_LEFT_BRACKET",         /* [ */
    "GLFW_KEY_BACKSLASH",            /* \ */
    "GLFW_KEY_RIGHT_BRACKET",        /* ] */
    "",
    "",
    "GLFW_KEY_GRAVE_ACCENT",         /* ` */
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "GLFW_KEY_WORLD_1",          /* non-US #1 */
    "GLFW_KEY_WORLD_2",          /* non-US #2 */
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    //  Function keys 
    "GLFW_KEY_ESCAPE",
    "GLFW_KEY_ENTER",
    "GLFW_KEY_TAB",
    "GLFW_KEY_BACKSPACE",
    "GLFW_KEY_INSERT",
    "GLFW_KEY_DELETE",
    "GLFW_KEY_RIGHT",
    "GLFW_KEY_LEFT",
    "GLFW_KEY_DOWN",
    "GLFW_KEY_UP",
    "GLFW_KEY_PAGE_UP",
    "GLFW_KEY_PAGE_DOWN",
    "GLFW_KEY_HOME",
    "GLFW_KEY_END",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "GLFW_KEY_CAPS_LOCK",
    "GLFW_KEY_SCROLL_LOCK",
    "GLFW_KEY_NUM_LOCK",
    "GLFW_KEY_PRINT_SCREEN",
    "GLFW_KEY_PAUSE",
    "",
    "",
    "",
    "",
    "",
    "GLFW_KEY_F1",
    "GLFW_KEY_F2",
    "GLFW_KEY_F3",
    "GLFW_KEY_F4",
    "GLFW_KEY_F5",
    "GLFW_KEY_F6",
    "GLFW_KEY_F7",
    "GLFW_KEY_F8",
    "GLFW_KEY_F9",
    "GLFW_KEY_F10",
    "GLFW_KEY_F11",
    "GLFW_KEY_F12",
    "GLFW_KEY_F13",
    "GLFW_KEY_F14",
    "GLFW_KEY_F15",
    "GLFW_KEY_F16",
    "GLFW_KEY_F17",
    "GLFW_KEY_F18",
    "GLFW_KEY_F19",
    "GLFW_KEY_F20",
    "GLFW_KEY_F21",
    "GLFW_KEY_F22",
    "GLFW_KEY_F23",
    "GLFW_KEY_F24",
    "GLFW_KEY_F25",
    "",
    "",
    "",
    "",
    "",
    "GLFW_KEY_KP_0",
    "GLFW_KEY_KP_1",
    "GLFW_KEY_KP_2",
    "GLFW_KEY_KP_3",
    "GLFW_KEY_KP_4",
    "GLFW_KEY_KP_5",
    "GLFW_KEY_KP_6",
    "GLFW_KEY_KP_7",
    "GLFW_KEY_KP_8",
    "GLFW_KEY_KP_9",
    "GLFW_KEY_KP_DECIMAL",
    "GLFW_KEY_KP_DIVIDE",
    "GLFW_KEY_KP_MULTIPLY",
    "GLFW_KEY_KP_SUBTRACT",
    "GLFW_KEY_KP_ADD",
    "GLFW_KEY_KP_ENTER",
    "GLFW_KEY_KP_EQUAL",
    "",
    "",
    "",
    "GLFW_KEY_LEFT_SHIFT",
    "GLFW_KEY_LEFT_CONTROL",
    "GLFW_KEY_LEFT_ALT",
    "GLFW_KEY_LEFT_SUPER",
    "GLFW_KEY_RIGHT_SHIFT",
    "GLFW_KEY_RIGHT_CONTROL",
    "GLFW_KEY_RIGHT_ALT",
    "GLFW_KEY_RIGHT_SUPER",
    "GLFW_KEY_MENU"
};

    // class Shader {
    //     public:
    //         unsigned int ID;
    //         Shader(const char* vertexPath, const char* fragmentPath) { // constructor generates the shader on the fly
    //             // 1. retrieve the vertex/fragment source code from filePath
    //             std::string vertexCode;
    //             std::string fragmentCode;
    //             std::ifstream vShaderFile;
    //             std::ifstream fShaderFile;
    //             // ensure ifstream objects can throw exceptions:
    //             vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    //             fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    //             try {
                    
    //                 vShaderFile.open(vertexPath);   // open files
    //                 fShaderFile.open(fragmentPath); //
    //                 std::stringstream vShaderStream, fShaderStream;
    //                 vShaderStream << vShaderFile.rdbuf();   // read file's buffer contents into streams
    //                 fShaderStream << fShaderFile.rdbuf();   //
    //                 vShaderFile.close();    // close file handlers
    //                 fShaderFile.close();    //
    //                 vertexCode   = vShaderStream.str(); // convert stream into string
    //                 fragmentCode = fShaderStream.str(); //
    //             }
    //             catch (std::ifstream::failure& e) {
    //                 std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl; //send error
    //             }
    //             const char* vShaderCode = vertexCode.c_str();
    //             const char * fShaderCode = fragmentCode.c_str();
    //             // 2. compile shaders
    //             unsigned int vertex, fragment;
    //             vertex = glCreateShader(GL_VERTEX_SHADER);          // vertex shader
    //             glShaderSource(vertex, 1, &vShaderCode, NULL);      //
    //             glCompileShader(vertex);                            //
    //             checkCompileErrors(vertex, "VERTEX");               //
    //             fragment = glCreateShader(GL_FRAGMENT_SHADER);      // fragment Shader  
    //             glShaderSource(fragment, 1, &fShaderCode, NULL);    //
    //             glCompileShader(fragment);                          //
    //             checkCompileErrors(fragment, "FRAGMENT");           //
    //             ID = glCreateProgram();                             // shader Program
    //             glAttachShader(ID, vertex);                         //
    //             glAttachShader(ID, fragment);                       //
    //             glLinkProgram(ID);                                  //
    //             checkCompileErrors(ID, "PROGRAM");                  //
    //             glDeleteShader(vertex);                             // delete the shaders as they're linked into our program now and no longer necessary
    //             glDeleteShader(fragment);                           //
    //         }
    //         void use() {       // activate the shader
    //             glUseProgram(ID); 
    //         }
    //         void setBool(const std::string &name, bool value) const {           // utility uniform functions
    //             glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    //         }
    //         void setInt(const std::string &name, int value) const {             //
    //             glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    //         }
    //         void setFloat(const std::string &name, float value) const {         //
    //             glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    //         }
    //     private:
    //         void checkCompileErrors(unsigned int shader, std::string type) {    // utility function for checking shader compilation/linking errors.
    //             int success;
    //             char infoLog[1024];
    //             if (type != "PROGRAM") {
    //                 glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    //                 if (!success) {
    //                     glGetShaderInfoLog(shader, 1024, NULL, infoLog);
    //                     std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    //                 }
    //             } else {
    //                 glGetProgramiv(shader, GL_LINK_STATUS, &success);
    //                 if (!success) {
    //                     glGetProgramInfoLog(shader, 1024, NULL, infoLog);
    //                     std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    //                 }
    //             }
    //         }
    //         //Mistical::Console ConsoleClass;
    //     };


// class Texture {
    //     public:
    //         GLFWimage load(const char* path) {
    //             src.pixels = stbi_load(path, &src.width, &src.height, nullptr, 4);
    //         }
    //     private:
    //         GLFWimage src;
    // };

    
    // bool Window::WindowInput::WindowInputMouse::isReleased(int btn) {
    //     if (glfwGetKey(window.window, key) == GLFW_RELEASE) { return true; }
    //     return false;
    // }
    // bool Window::WindowInput::WindowInputMouse::isPressed(int btn) {
    //     if (glfwGetKey(window.window, key) == GLFW_PRESS) { return true; }
    //     return false;
    // }
    // bool Window::WindowInput::WindowInputMouse::wasPressed(int btn) {
    //     glfwGetCursorPos(window.window, &window.cursorPos[0], &window.cursorPos[1]);
    //     // https://www.glfw.org/docs/3.3/input_guide.html#input_mouse
    // }
    // bool Window::WindowInput::WindowInputMouse::wasReleased(int btn) {
    //     if (glfwGetKey(window.window, key) == GLFW_RELEASE && pressedKeys[key] == true) {
    //         pressedKeys[key] = false;
    //         return true;
    //     }
    //     checkKeyPress(key);
    //     return false;
    // }

    
    
/*
    enum class TileSetSizes {
        SimpleTile,
        ThreeByThree,
        FiveByFive
    };
    enum class TileSetTypes {
        BackGround,
        Ground,
        ForeGround
    };
    class TileSet {
        public:
            TileSet(ObjectIdentifier id, const char* assetPath);
        private:
            TileSetTypes layer;
            TileSetSizes size;
            const static int gridWidth = 40;
            const static int gridHeigth = 23;
    };
    TileSet::TileSet(ObjectIdentifier id, const char* assetsPath) {}

    class Tile {

    };

*/  