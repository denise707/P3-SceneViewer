#include "ModelLoaderThread.h"
#include "GameObject.h"
#include "Mesh.h"
#include "GraphicsEngine.h"
#include "MeshComponent.h"
#include "GameObjectManager.h"
#include <string>
#include <random>
#include "TransformComponent.h"

ModelLoaderThread::ModelLoaderThread(const wchar_t* fileDir, std::string name, IETSemaphore* mutex, std::vector<GameObject*>* gameObjectList, IExecutionEvent* execEvent)
{
    this->fileDir = fileDir;
    this->name = name;
    this->mutex = mutex;
    this->gameObjectList = gameObjectList;
    this->execEvent = execEvent;
    this->isRunning = true;
}

ModelLoaderThread::~ModelLoaderThread()
{
    
}

void ModelLoaderThread::destroy()
{
    delete this;
}

void ModelLoaderThread::run()
{
    while (this->isRunning) {
        GameObject* obj = GameObject::Instantiate(name);

        Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(fileDir);

        MeshComponent* meshComponent = new MeshComponent();
        obj->AttachComponent(meshComponent);
        meshComponent->SetMesh(mesh);

        //Randomize Position
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, 2.5f); // define the range

        obj->GetTransform()->SetPosition({ (float)distr(gen), 0, (float)distr(gen) });

        mutex->acquire();
        IETThread::sleep(50);
        if (this->isRunning) {
            this->execEvent->OnFinishedExecution();
            this->gameObjectList->push_back(obj);
        }
            
        mutex->release();

        
        isRunning = false;

        std::cout << name << "leave" << std::endl;
    }

    delete this;
}
