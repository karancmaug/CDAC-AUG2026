#include <iostream>
#include <memory>
using namespace std;

class Texture {
  string name;
  int width;
  int height;

public:
  Texture(const string &name, const int &width, const int &height)
      : name(name), width(width), height(height) {
    cout << " Texture Loaded" << endl;
  }

  ~Texture() { cout << "Texture Realeased" << endl; }

  void display() const {
    cout << "Width ->" << width << endl;
    cout << "Height ->" << height << endl;
  }
};

class Shader{
    string name;
    string type; // "vertex" / "fragment"

    public : 

    Shader(const string& name, const string& type) : name(name), type(type){
        cout << "Shader Compiled" << endl;
    }

    ~Shader(){
        cout << "Shader Destroyed" << endl;
    }

    int getReferenceCount(const shared_ptr<Shader>& ptr){
            return ptr.use_count();
    }
};

class AudioClip{
    string name;
    int freq; // "vertex" / "fragment"

    public : 

    AudioClip(const string& name, const int& freq) : name(name), freq(freq){
        cout << "AudioClip Loaded" << endl;
    }

    ~AudioClip(){
        cout << "AudioCLip Unloaded" << endl;
    }

    string getName() const{
        return this->name;
    }

    int getReferenceCount(const shared_ptr<AudioClip>& ptr){
            return ptr.use_count();
    }
};

int main() {

    //Part A
    cout << endl;
    cout << "Part A" << endl;
    cout << endl;
    unique_ptr<Texture> tex1 = make_unique<Texture>("player_sprite", 512, 512);
    tex1->display();
    // unique_ptr<Texture> tex2 = tex1; A unique ptr cannot be copied
    // because it has exclusive ownership of the resource
    // if we want to copy it we can use std::move to transfer the ownership
    // Or we can use std::shared_ptr which allows multiple pointers to own the
    // same resource
    unique_ptr<Texture> tex2 = std::move(tex1); // this transfers the ownership of tex1 to tex2
    cout << "tex1 is null: " << (tex1 == nullptr ? "YES" : "NO") << endl;
        
    //------------------------------------------------------------------------------------------------------

    // Part B
    cout << endl;
    cout << " Part B" << endl;
    cout << endl;
    shared_ptr<Shader> shader = make_shared<Shader>("main_vert","vertex");
    cout << "Ref count: " << shader->getReferenceCount(shader) << endl;

    {
        auto rendererRef = shader;
        cout << "Ref count:" << rendererRef->getReferenceCount(rendererRef) << endl;

        auto editorRef = rendererRef;
        cout << "Ref count:" << editorRef->getReferenceCount(editorRef)<< endl;
    }
    
    cout << "Ref count: " << shader->getReferenceCount(shader) << endl;
    
    //--------------------------------------------------------------------------------------------------------------------

    //PART C
    cout << endl;
    cout << " Part C" << endl;
    cout << endl;

    auto audio = make_shared<AudioClip>("explosion",3.5);
    weak_ptr<AudioClip> observer =audio;

    if (auto clip = observer.lock())
    cout << "Clip alive: " << clip->getName() << endl;

    audio.reset();

    if (observer.expired())
    cout << "Clip already unloaded." << endl;


    return 0;
}