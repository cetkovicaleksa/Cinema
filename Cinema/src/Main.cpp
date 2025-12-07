#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Util.h"

constexpr double 
    MIN_FRAME_DURATION_SECONDS = 1.0 / 75.0, 
    PROJECTION_DURATION_SECONDS = 20.0;

constexpr int
    CANVAS_COLOUR_DURATION_FRAMES = 20; 

GLFWcursor *cursor, *cursorPressed;
int width = 800, height = 800;

double projectionEndTime = -1.0;
float cR(1), cB(1), cG(1);

constexpr int ROWS = 5, COLS = 10;

struct Seat {
    enum State { FREE, RESERVED, PURCHASED };

    State state;
    float x, y;

    const bool isAt(double mx, double my) {
        constexpr double half = 0.08f;

        return mx > (x - half) && mx < (x + half) &&
            my >(y - half) && my < (y + half);
    }
};

Seat seats[ROWS][COLS];

void initSeats() {
    float seatScale = 0.04f;
    float seatSize = seatScale * 2.0f;
    float spacing = seatSize * 2.2f;  

    float totalWidth = COLS * spacing;
    float startX = -totalWidth / 2.0f + spacing / 2.0f;

    float centerY = -0.4f;
    float totalHeight = ROWS * spacing;
    float startY = centerY + totalHeight / 2.0f - spacing / 2.0f;

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            seats[r][c].x = startX + c * spacing;
            seats[r][c].y = startY - r * spacing;
            seats[r][c].state = Seat::FREE;
        }
    }
}


void purchaseFirstNFreeSeats(int n) {
    for (int r = ROWS - 1; r >= 0 && n > 0; --r) {
        for (int c = COLS - 1; c >= 0 && n > 0; --c) {
            if (seats[r][c].state == Seat::FREE) {
                seats[r][c].state = Seat::PURCHASED;
                --n;
            }
        }
    }
}


void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT: 
            glfwSetCursor(window, action == GLFW_PRESS ? cursorPressed : cursor);

            if (action == GLFW_PRESS && projectionEndTime == -1) {
                double mx, my;
                glfwGetCursorPos(window, &mx, &my);

                // Convert to [-1, 1]
                mx = (mx / width) * 2.0f - 1.0f;
                my = 1.0 - (my / height) * 2.0;

                for (int r = 0; r < ROWS; r++) {
                    for (int c = 0; c < COLS; c++) {
                        Seat &s = seats[r][c];

                        if (s.isAt(mx, my)) {
                            if (s.state == Seat::State::FREE)
                                s.state = Seat::State::RESERVED;
                            else if (s.state == Seat::State::RESERVED)
                                s.state = Seat::State::FREE;

                            r = ROWS;
                            break;
                        }
                    }
                }
            }
            break;
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (key) {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, action == GLFW_PRESS ? GLFW_TRUE : GLFW_FALSE);
        break;
    case GLFW_KEY_ENTER:
        if (action == GLFW_PRESS && projectionEndTime == -1) {
            projectionEndTime = glfwGetTime() + PROJECTION_DURATION_SECONDS;
        }
        break;
    default:
        if (action == GLFW_PRESS && key >= GLFW_KEY_0 && key <= GLFW_KEY_9 && projectionEndTime == -1) {
            int n = key - GLFW_KEY_0;
            purchaseFirstNFreeSeats(n);
        }
        break;
    }
}

void formVAOs(
    float *verticesCanvas, size_t canvasSize, unsigned int &VAOcanvas,
    float* verticesOverlay, size_t overlaySize, unsigned int& VAOoverlay,
    float* verticesSeat, size_t seatSize, unsigned int& VAOseat
) {
    // Canvas
    unsigned VBOcanvas;
    glGenVertexArrays(1, &VAOcanvas);
    glGenBuffers(1, &VBOcanvas);

    glBindVertexArray(VAOcanvas);
    glBindBuffer(GL_ARRAY_BUFFER, VBOcanvas);
    glBufferData(GL_ARRAY_BUFFER, canvasSize, verticesCanvas, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Overlay
    unsigned VBOoverlay;
    glGenVertexArrays(1, &VAOoverlay);
    glGenBuffers(1, &VBOoverlay);

    glBindVertexArray(VAOoverlay);
    glBindBuffer(GL_ARRAY_BUFFER, VBOoverlay);
    glBufferData(GL_ARRAY_BUFFER, overlaySize, verticesOverlay, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Seat
    unsigned VBOseat;
    glGenVertexArrays(1, &VAOseat);
    glGenBuffers(1, &VBOseat);

    glBindVertexArray(VAOseat);
    glBindBuffer(GL_ARRAY_BUFFER, VBOseat);
    glBufferData(GL_ARRAY_BUFFER, seatSize, verticesSeat, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    initSeats();

    auto *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    width = mode->width;
    height = mode->height;

    GLFWwindow *window = glfwCreateWindow(
        width,
        height,
        "Cinema",
        monitor,
        NULL
    );
    if (window == NULL) return endProgram("Prozor nije uspeo da se kreira.");
    glfwMakeContextCurrent(window);

    cursor = loadImageToCursor("res/cursor.png");
    cursorPressed = loadImageToCursor("res/cursorpress.png");
    glfwSetCursor(window, cursor);
    
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetKeyCallback(window, keyCallback);

    if (glewInit() != GLEW_OK) return endProgram("GLEW nije uspeo da se inicijalizuje.");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    unsigned
        rectShader = createShader("res/rect.vert", "res/rect.frag");

    //region vertices

    float verticesCanvas[] = {
        -0.5f,  0.5f,
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f 
    };

    float verticesOverlay[] = {
        -1.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, -1.0f,
        1.0f, 1.0f
    };

    float verticesSeat[] = {
        // Backrest
        -0.55f, 0.5f,
        -0.55f, 0.1f,
        0.55f, 0.1f,
        0.55f, 0.5f,

        // Cushion
        -0.6f,-0.1f,
        -0.6f,-0.5f,
        0.6f,-0.5f,
        0.6f,-0.1f,

        // Left armrest
        -0.75f, 0.3f,
        -0.75f,-0.3f,
        -0.6f, -0.3f,
        -0.6f,  0.3f,

        // Right armrest
        0.75f, 0.3f,
        0.75f,-0.3f,
        0.6f, -0.3f,
        0.6f,  0.3f
    };

    //endregion

    //region VAOs
    
    unsigned VAOcanvas, VAOoverlay, VAOseat;

    formVAOs(
        verticesCanvas, sizeof(verticesCanvas), VAOcanvas,
        verticesOverlay, sizeof(verticesOverlay), VAOoverlay,
        verticesSeat, sizeof(verticesSeat), VAOseat
    );

    //endregion

    glClearColor(0.2f, 0.8f, 0.6f, 1.0f);

    for (int frameCnt = 0; !glfwWindowShouldClose(window); ++frameCnt)
    {
        const double initFrameTime = glfwGetTime();
        const bool isProjecting = initFrameTime < projectionEndTime;

        glClear(GL_COLOR_BUFFER_BIT);
        
        // draw canvas
        if (!isProjecting /* && people entered */) {
            cR = cG = cB = 1;
        }
        else if (cR == 1 && cG == 1 && cB == 1 || (frameCnt %= CANVAS_COLOUR_DURATION_FRAMES) == 0) {
            cR = static_cast<float>(rand()) / RAND_MAX;
            cG = static_cast<float>(rand()) / RAND_MAX;
            cB = static_cast<float>(rand()) / RAND_MAX;
        }
        
        glUseProgram(rectShader);

        glUniform4f(glGetUniformLocation(rectShader, "uColor"), cR, cG, cB, 1);
        glUniform2f(glGetUniformLocation(rectShader, "uScale"), 0.6f, 0.4f);
        glUniform2f(glGetUniformLocation(rectShader, "uOffset"), 0.0f, 0.5f);

        glBindVertexArray(VAOcanvas);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        // draw seats
        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLS; ++c) {
                auto &seat = seats[r][c];
                float sr, sg, sb;

                switch (seat.state) {
                case Seat::PURCHASED:  // red
                    sr = 1; sg = 0; sb = 0;
                    break;

                case Seat::RESERVED:   // yellow
                    sr = 1; sg = 1; sb = 0;
                    break;

                case Seat::FREE:       // blue
                default:
                    sr = 0; sg = 0; sb = 1;
                    break;
                }

                glUseProgram(rectShader);
                glUniform4f(glGetUniformLocation(rectShader, "uColor"), sr, sg, sb, 1);
                glUniform2f(glGetUniformLocation(rectShader, "uScale"), 0.08f, 0.08f);
                glUniform2f(glGetUniformLocation(rectShader, "uOffset"), seat.x, seat.y);

                glBindVertexArray(VAOseat);
                glDrawArrays(GL_TRIANGLE_FAN, 0, 4);   // backrest
                glDrawArrays(GL_TRIANGLE_FAN, 4, 4);   // cushion
                glDrawArrays(GL_TRIANGLE_FAN, 8, 4);   // left armrest
                glDrawArrays(GL_TRIANGLE_FAN, 12, 4);  // right armrest
            }
        }

        // draw overlay
        if (!isProjecting) {
            glUseProgram(rectShader);
            glUniform4f(glGetUniformLocation(rectShader, "uColor"), .1f, .1f, .1f, .5f);
            glUniform2f(glGetUniformLocation(rectShader, "uScale"), 1.0f, 1.0f);
            glUniform2f(glGetUniformLocation(rectShader, "uOffset"), .0f, .0f);

            glBindVertexArray(VAOoverlay);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        while (glfwGetTime() - initFrameTime < MIN_FRAME_DURATION_SECONDS) {}

        if (isProjecting && glfwGetTime() >= projectionEndTime || projectionEndTime != -1 && (glfwGetTime() - projectionEndTime) > PROJECTION_DURATION_SECONDS) {
            projectionEndTime = -1;
            initSeats();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
