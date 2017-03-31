#include "scene.h"

Scene::Scene( void )
{}

Scene::~Scene( void )
{}

bool Scene::intersect( const Ray &ray,
                       IntersectionRecord &intersection_record ) const
{
    bool intersection_result = false;
    IntersectionRecord tmp_intersection_record;
    std::size_t num_primitives = primitives_.size();

    // Loops over the list of primitives, testing the intersection of each primitive against the given ray 
    for ( std::size_t primitive_id = 0; primitive_id < num_primitives; primitive_id++ )
        if ( primitives_[primitive_id]->intersect( ray, tmp_intersection_record ) )
            if ( ( tmp_intersection_record.t_ < intersection_record.t_ ) && ( tmp_intersection_record.t_ > 0.0 ) )
            {
                intersection_record = tmp_intersection_record;
                intersection_result = true; // the ray intersects a primitive!
            }

    return intersection_result;
}

void Scene::load( void ) 
{
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.0f, 5.0f }, 0.5f, glm::vec3{  0.0f, 0.0f,   0.0f }, 1 } ) );
/*    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.5f,-1.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f,-0.5f,-1.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f,-0.5f,-1.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f, 0.5f,-2.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.5f,-2.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f,-0.5f,-2.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f,-0.5f,-2.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f, 0.5f,-3.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.5f,-3.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f,-0.5f,-3.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f,-0.5f,-3.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f, 0.5f,-4.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.5f,-4.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f,-0.5f,-4.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f,-0.5f,-4.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f, 0.5f,-5.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.5f,-5.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f,-0.5f,-5.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f,-0.5f,-5.0f }, 0.2f, glm::vec3{  0.0f, 0.0f,   0.0f } } ) );

*/
    //fundo
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{-3.0f ,3.0f , -4.0f}, glm::vec3{3.0f,3.0f,-4.0f}, glm::vec3{3.0f, -3.0f,-4.0f},
                                                                            glm::vec3{0.9f, 0.89f , 0.24f},
                                                                            0}));
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{-3.0f ,3.0f , -4.0f}, glm::vec3{-3.0f,-3.0f,-4.0f}, glm::vec3{3.0f, -3.0f,-4.0f},
                                                                            glm::vec3{0.9f, 0.89f , 0.24f},
                                                                            0}));    
    //parede direita                                                                        
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{3.0f ,3.0f , 5.0f}, glm::vec3{3.0f,3.0f,-4.0f}, glm::vec3{3.0f, -3.0f,-4.0f},
                                                                            glm::vec3{0.0f, 1.0f , 0.0f},
                                                                            0}));
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{3.0f ,3.0f , 5.0f}, glm::vec3{3.0f,-3.0f,5.0f}, glm::vec3{3.0f, -3.0f,-4.0f},
                                                                            glm::vec3{0.0f, 1.0f , 0.0f},
                                                                            0}));  

    //parede esquerda
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{-3.0f ,3.0f , 5.0f}, glm::vec3{-3.0f,3.0f,-4.0f}, glm::vec3{-3.0f, -3.0f,-4.0f},
                                                                            glm::vec3{1.0f, 0.0f , 0.0f},
                                                                            0}));
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{-3.0f ,3.0f , 5.0f}, glm::vec3{-3.0f,-3.0f,5.0f}, glm::vec3{-3.0f, -3.0f,-4.0f},
                                                                            glm::vec3{1.0f, 0.0f , 0.0f},
                                                                            0}));       
    //teto
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{-3.0f ,3.0f , -4.0f}, glm::vec3{-3.0f,3.0f,4.0f}, glm::vec3{3.0f, 3.0f,4.0f},
                                                                            glm::vec3{0.9f, 0.89f , 0.24f},
                                                                            0}));
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{-3.0f ,3.0f , -4.0f}, glm::vec3{3.0f,3.0f,4.0f}, glm::vec3{3.0f, 3.0f,-4.0f},
                                                                            glm::vec3{0.9f, 0.89f , 0.24f},
                                                                            0}));                                                                       
    //chao
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{-3.0f ,-3.0f , -4.0f}, glm::vec3{3.0f,-3.0f,-4.0f}, glm::vec3{-3.0f, -3.0f,4.0f},
                                                                            glm::vec3{0.2f, 0.2f , 0.2f},
                                                                            0}));
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{3.0f ,-3.0f , -4.0f}, glm::vec3{3.0f,-3.0f,4.0f}, glm::vec3{-3.0f, -3.0f,4.0f},
                                                                            glm::vec3{0.2f, 0.2f , 0.2f},
                                                                            0})); 



}

void Scene::loadObject(const char * obj)
{
    Assimp::Importer importer;
    
    const aiScene* scene = importer.ReadFile(obj, aiProcess_Triangulate);

    unsigned int i = 0, j;

    srand(std::time(0));

    for(j = 0; (j+1)<= scene->mMeshes[i]->mNumFaces; j++){

        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

       

        primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{(float)scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[0]].x, 
                                                                                      (float)scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[0]].y, 
                                                                                      (float)scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[0]].z},
                                                                                      
                                                                            glm::vec3{(float)scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[1]].x,
                                                                                      (float)scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[1]].y,
                                                                                      (float)scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[1]].z},

                                                                            glm::vec3{(float)scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[2]].x,
                                                                                      (float)scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[2]].y,
                                                                                      (float)scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[j].mIndices[2]].z},
                                                                                                                                                                                 
                                                                            glm::vec3{r, g, b},//random color 
                                                                            0})); //material type 
    }
}

