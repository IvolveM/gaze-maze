
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iterator>

class Mesh {
    protected:
        glm::vec3   position, size;
        // glm::vec3   color;
        // float       rotation;

        bool instancing;
        std::vector<glm::mat4> instanceModelMatrices;

    public:
        virtual ~Mesh();
        Mesh(glm::vec3 position);
        // instancing constructor
        Mesh(std::vector<glm::vec3> instancePositions);

        // void rotate(float angleInDegrees) { this->rotation += angleInDegrees; };
        void move(glm::vec3 pos) { this->position += pos; };
        // void setSize (glm::vec3 size) { this->size = size; };
        // void setColor (glm::vec3 col) { this->color = col; };
        // void setVertices(float vertices[]) { this->vertices.insert(this->vertices.end(), vertices, vertices + sizeof(vertices)/sizeof(float)); };
        // void addVertex(float vertex) { this->vertices.push_back(vertex); }

        virtual void draw();
};