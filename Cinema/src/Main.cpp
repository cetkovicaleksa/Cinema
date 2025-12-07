#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <random>

#define STB_EASY_FONT_IMPLEMENTATION
#include "stb_easy_font.h"

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

struct Door {
    float x, y;
    float width, height;
    bool open;
    float currentWidth;
};

Door door = { -.99f, .2f, 0.2f, 0.05f, false, 0.2f };
float doorMaxWidth = 0.6f, doorSpeed = 0.01f;

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

void startProjection() {
    projectionEndTime = glfwGetTime() + PROJECTION_DURATION_SECONDS;
    door.open = true;
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
            startProjection();
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
    float* verticesSeat, size_t seatSize, unsigned int& VAOseat,
    float* verticesDoor, size_t doorSize, unsigned int& VAOdoor,
    float* verticesTextBg, size_t textBgSize, unsigned int& VAOtextBg
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

    unsigned VBOdoor;
    glGenVertexArrays(1, &VAOdoor);
    glGenBuffers(1, &VBOdoor);

    glBindVertexArray(VAOdoor);
    glBindBuffer(GL_ARRAY_BUFFER, VBOdoor);
    glBufferData(GL_ARRAY_BUFFER, doorSize, verticesDoor, GL_STATIC_DRAW);
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
        rectShader = createShader("res/rect.vert", "res/rect.frag"),
        textShader = createShader("res/text.vert", "res/text.frag");

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

    float verticesDoor[] = {
        -0.5f,  0.5f,
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f
    };

    //endregion

    //region VAOs

    unsigned VAOcanvas, VAOoverlay, VAOseat, VAOdoor, VAOtextBg;

    formVAOs(
        verticesCanvas, sizeof(verticesCanvas), VAOcanvas,
        verticesOverlay, sizeof(verticesOverlay), VAOoverlay,
        verticesSeat, sizeof(verticesSeat), VAOseat,
        verticesDoor, sizeof(verticesDoor), VAOdoor,
        verticesCanvas, sizeof(verticesCanvas), VAOtextBg
    );

    unsigned VAOtext, VBOtext;
    glGenVertexArrays(1, &VAOtext);
    glGenBuffers(1, &VBOtext);
    glBindVertexArray(VAOtext);
    glBindBuffer(GL_ARRAY_BUFFER, VBOtext);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 100000, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

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

        // door opening/closing logic
        if (door.open && door.currentWidth < doorMaxWidth) {
            door.currentWidth += doorSpeed;
            if (door.currentWidth > doorMaxWidth) door.currentWidth = doorMaxWidth;
        }
        if (!door.open && door.currentWidth > door.width) {
            door.currentWidth -= doorSpeed;
            if (door.currentWidth < door.width) door.currentWidth = door.width;
        }

        // draw door
        glUseProgram(rectShader);
        glUniform4f(glGetUniformLocation(rectShader, "uColor"), 0.5f, 0.25f, 0.0f, 1.0f); // brown
        glUniform2f(glGetUniformLocation(rectShader, "uScale"), (door.currentWidth / doorMaxWidth) * .05f, .15f);
        glUniform2f(glGetUniformLocation(rectShader, "uOffset"), door.x, door.y);

        glBindVertexArray(VAOdoor);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);



        // draw overlay
        if (!isProjecting) {
            glUseProgram(rectShader);
            glUniform4f(glGetUniformLocation(rectShader, "uColor"), .1f, .1f, .1f, .5f);
            glUniform2f(glGetUniformLocation(rectShader, "uScale"), 1.0f, 1.0f);
            glUniform2f(glGetUniformLocation(rectShader, "uOffset"), .0f, .0f);

            glBindVertexArray(VAOoverlay);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        }

        // draw text background
        glUseProgram(rectShader);
        glUniform4f(glGetUniformLocation(rectShader, "uColor"), 0.1f, 0.1f, 0.1f, 0.6f);
        glUniform2f(glGetUniformLocation(rectShader, "uScale"), .3f, .08f);
        glUniform2f(glGetUniformLocation(rectShader, "uOffset"), .8f, -.89f);

        glBindVertexArray(VAOtextBg);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        // draw text 
        static float buffer[99999];
        static float vertex_buffer[99999];
        int num_quads;

        num_quads = stb_easy_font_print(0, 0, (char*)"SV77/2022 Aleksa Cetkovic", NULL, buffer, sizeof(buffer));

        // Convert quads to triangles and flip Y coordinate
        int vertex_count = 0;
        for (int i = 0; i < num_quads; i++) {
            float* quad = buffer + i * 16; // 4 vertices * 4 floats (x,y,z,w)

            // First triangle (0, 1, 2)
            vertex_buffer[vertex_count++] = quad[0];  // x
            vertex_buffer[vertex_count++] = -quad[1]; // -y (flip vertically)
            vertex_buffer[vertex_count++] = quad[2];  // z
            vertex_buffer[vertex_count++] = quad[3];  // w

            vertex_buffer[vertex_count++] = quad[4];  // x
            vertex_buffer[vertex_count++] = -quad[5]; // -y
            vertex_buffer[vertex_count++] = quad[6];  // z
            vertex_buffer[vertex_count++] = quad[7];  // w

            vertex_buffer[vertex_count++] = quad[8];  // x
            vertex_buffer[vertex_count++] = -quad[9]; // -y
            vertex_buffer[vertex_count++] = quad[10]; // z
            vertex_buffer[vertex_count++] = quad[11]; // w

            // Second triangle (0, 2, 3)
            vertex_buffer[vertex_count++] = quad[0];  // x
            vertex_buffer[vertex_count++] = -quad[1]; // -y
            vertex_buffer[vertex_count++] = quad[2];  // z
            vertex_buffer[vertex_count++] = quad[3];  // w

            vertex_buffer[vertex_count++] = quad[8];  // x
            vertex_buffer[vertex_count++] = -quad[9]; // -y
            vertex_buffer[vertex_count++] = quad[10]; // z
            vertex_buffer[vertex_count++] = quad[11]; // w

            vertex_buffer[vertex_count++] = quad[12]; // x
            vertex_buffer[vertex_count++] = -quad[13]; // -y
            vertex_buffer[vertex_count++] = quad[14]; // z
            vertex_buffer[vertex_count++] = quad[15]; // w
        }

        glUseProgram(textShader);

        float textScale = 3.0f;
        float textX = width * 0.77f;
        float textY = height * 0.93f;
        float scaleX = textScale * 2.0f / width;
        float scaleY = textScale * 2.0f / height;

        glUniform2f(glGetUniformLocation(textShader, "uOffset"), textX * 2.0f / width - 1.0f, 1.0f - textY * 2.0f / height);
        glUniform2f(glGetUniformLocation(textShader, "uScale"), scaleX, scaleY);
        glUniform4f(glGetUniformLocation(textShader, "uColor"), 1.0f, 1.0f, 1.0f, 1.0f);

        glBindVertexArray(VAOtext);
        glBindBuffer(GL_ARRAY_BUFFER, VBOtext);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_count * sizeof(float), vertex_buffer);

        glDrawArrays(GL_TRIANGLES, 0, num_quads * 6);

        glfwSwapBuffers(window);
        glfwPollEvents();

        while (glfwGetTime() - initFrameTime < MIN_FRAME_DURATION_SECONDS) {}

        if (isProjecting && glfwGetTime() >= projectionEndTime || projectionEndTime != -1 && (glfwGetTime() - projectionEndTime) > PROJECTION_DURATION_SECONDS) {
            projectionEndTime = -1;
            door.open = false; /* wait for people to go out */
            initSeats();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
