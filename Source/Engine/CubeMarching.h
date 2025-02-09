#pragma once
#include <vector>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "../FastNoiseLite.h"
static const short WIDTH = 1000;
static const short HEIGHT = 100;
static const short DEPTH = 1000;

float noiseScale = 0.492f;
float persistence = 0.295f;
float lacunarity = 2.459f;
int octaves = 4;


std::vector<glm::vec3> vertices;
std::vector<glm::vec3> normals;
std::vector<glm::vec2> UV;
std::vector<unsigned int> indices;
short voxels[WIDTH][HEIGHT][DEPTH] = {0};

inline void ClearData()
{
    vertices.clear();
    normals.clear();
    UV.clear();
    indices.clear();
    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++) // Correct order: y is in the middle
        {
            for (int z = 0; z < DEPTH; z++)
            {
                voxels[x][y][z] = 0; // Corrected indexing
            }
        }
    }
}

inline void generateTerrain()
{
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

    for (int x = 0; x < WIDTH; x++)
    {
        for (int z = 0; z < DEPTH; z++)
        {
            float amplitude = 1;
            float frequency = 1;
            float noiseHeight = 0;

            for (int i = 0; i < octaves; i++)
            {
                float perlinValue = noise.GetNoise(float(x) * noiseScale * frequency, 
                                                   float(z) * noiseScale * frequency) * 0.5f + 0.5f;
                noiseHeight += perlinValue * amplitude;

                amplitude *= persistence;
                frequency *= lacunarity;
            }

            // Ensure noiseHeight is within bounds
            int maxHeight = std::min(HEIGHT - 1, static_cast<int>(noiseHeight * HEIGHT/(float)octaves));

            for (int y = 0; y <= maxHeight; y++)  // Fill up to the calculated height
            {
                voxels[x][y][z] = 1;
            }
        }
    }
}

inline bool isAir(int x, int y, int z)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || z < 0 || z >= DEPTH)
        return true; // Treat out-of-bounds as air
    return voxels[x][y][z] == 0;
}

inline void addFace(glm::vec3 pos, glm::vec3 normal, glm::vec2 uvStart)
{
    int index = vertices.size();

    // Define a quad with four vertices
    glm::vec3 tangent1(1, 0, 0);
    glm::vec3 tangent2(0, 1, 0);

    if (normal.x != 0) tangent1 = glm::vec3(0, 1, 0), tangent2 = glm::vec3(0, 0, 1);
    if (normal.y != 0) tangent1 = glm::vec3(1, 0, 0), tangent2 = glm::vec3(0, 0, 1);
    if (normal.z != 0) tangent1 = glm::vec3(1, 0, 0), tangent2 = glm::vec3(0, 1, 0);

    vertices.push_back(pos);
    vertices.push_back(pos + tangent1);
    vertices.push_back(pos + tangent2);
    vertices.push_back(pos + tangent1 + tangent2);

    normals.push_back(normal);
    normals.push_back(normal);
    normals.push_back(normal);
    normals.push_back(normal);

    UV.push_back(uvStart);
    UV.push_back(uvStart + glm::vec2(1, 0));
    UV.push_back(uvStart + glm::vec2(0, 1));
    UV.push_back(uvStart + glm::vec2(1, 1));

    indices.push_back(index);
    indices.push_back(index + 1);
    indices.push_back(index + 2);
    indices.push_back(index + 1);
    indices.push_back(index + 3);
    indices.push_back(index + 2);
}

inline void generateMesh()
{
    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            for (int z = 0; z < DEPTH; z++)
            {
                if (voxels[x][y][z] == 0) continue;

                if (isAir(x, y, z - 1)) addFace(glm::vec3(x, y, z), glm::vec3(0, 0, -1), glm::vec2(0, 0));
                // Front
                if (isAir(x, y, z + 1)) addFace(glm::vec3(x, y, z + 1), glm::vec3(0, 0, 1), glm::vec2(0, 0));
                // Back
                if (isAir(x - 1, y, z)) addFace(glm::vec3(x, y, z), glm::vec3(-1, 0, 0), glm::vec2(0, 0));
                // Left
                if (isAir(x + 1, y, z)) addFace(glm::vec3(x + 1, y, z), glm::vec3(1, 0, 0), glm::vec2(0, 0));
                // Right
                if (isAir(x, y - 1, z)) addFace(glm::vec3(x, y, z), glm::vec3(0, -1, 0), glm::vec2(0, 0));
                // Bottom
                if (isAir(x, y + 1, z)) addFace(glm::vec3(x, y + 1, z), glm::vec3(0, 1, 0), glm::vec2(0, 0));
                // Top
            }
        }
    }
}
