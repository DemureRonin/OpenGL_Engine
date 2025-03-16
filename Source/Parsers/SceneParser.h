#pragma once
#include <memory>
#include <vector>


class Prefab;

class SceneParser
{
public:
    static std::vector<std::shared_ptr<Prefab>> ParseScene(const char* assetPath);
};
