#pragma once

#include "Object.hpp"

namespace ofxVoxels {
    
    class Container : public Object {
        
    public:
        virtual string getName() = 0;
        
        template<class T>
        const shared_ptr<T> addChild(Registration side, Registration reg) {
            const shared_ptr<T> child = addChild<T>(reg);
            child->setSide(side);
            return child;
        }
        
        template<class T>
        const shared_ptr<T> addChild(Registration reg) {
            shared_ptr<T> child(new T);
            child->setParent(this);
            child->setRegistration(reg);
            children.push_back(child);
            return child;
        }
        
        template<class T>
        const shared_ptr<T> addChild() {
            return addChild<T>(Registration::TOP, Registration::BOTTOM);
        }
        
        template<class T>
        const shared_ptr<T> getChild(int index) {
            return static_pointer_cast<T>(children[index]);
        }
        
        void removeChild(const shared_ptr<Container> &child) {
            children.erase(std::remove(children.begin(), children.end(), child), children.end());
        }
        
        int countChildren() const {
            return children.size();
        }
        const vector<shared_ptr<Container>> &getChildren() const {
            return children;
        }
        Container * getParent() const {
            return parent;
        }
        void setParent(Container *value) {
            parent = value;
        }

        virtual void clear();
        virtual void update(const glm::mat4 &mat);
        
        virtual const glm::mat4 getChildMatrix(const shared_ptr<Container> &child) const {
            return getChildMatrix(child.get());
        }
        virtual const glm::mat4 getChildMatrix(const Container *child) const {
            return glm::mat4();
        }
        const glm::mat4 getGlobalTransformMatrix() const {
            if (parent != NULL) {
                return parent->getGlobalTransformMatrix() * parent->getChildMatrix(this) * localTransformMatrix;
            }
            return localTransformMatrix;
        }
        const glm::vec3 getGlobalPosition() const {
            return glm::vec3(getGlobalTransformMatrix() * glm::vec4(0.f, 0.f, 0.f, 1.f));
        }
        
    protected:
        Container * parent = NULL;
        vector<shared_ptr<Container>> children;
        
    };
    
}
