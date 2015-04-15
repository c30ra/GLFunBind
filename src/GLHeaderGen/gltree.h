/*******************************************************************************
GLFunBind type safe header only OpenGL function binder.
Copyright (C) 2015  Luca Carella

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/

#ifndef GLHEADERGEN_GLTREE_H
#define GLHEADERGEN_GLTREE_H

//Qt
#include <QString>
#include <QVector>

//System
#include <memory>

namespace GLHeaderGen {

  template<class T>
  class TreeNode
  {
  public:
    TreeNode(const QString &key)
      : m_key{key} {}

    //! return the node associated at key;
    TreeNode<T> *node(const QString &key) const
    {
      for(auto &v : m_node)
        if(v->key() == key)
          return v.get();
      return nullptr;
    }
    //! add a child node to node
    TreeNode<T> *addNode(const QString &key)
    {
      if(!m_node.empty())
        {
          for(auto &v : m_node)
            {
              if(v->key() == key)//node already exist
                return v.get();
            }
          auto node = std::make_shared<TreeNode<T>>(key);
          m_node.push_back(node);
          return node.get();
        }
      else
        {
          auto node = std::make_shared<TreeNode<T>>(key);
          m_node.push_back(node);
          return node.get();
        }
    }

    void setData(std::unique_ptr<T> &&data) Q_DECL_NOEXCEPT {m_data = std::move(data);}
    T* data(){return m_data.get();}
    //! return the key associated do this node
    QString key() const
    {
      return m_key;
    }

    std::vector<std::shared_ptr<TreeNode<T> > > nodes() const{return m_node;}

  private:
    QString m_key;
    std::unique_ptr<T> m_data;
    std::vector<std::shared_ptr<TreeNode<T>>> m_node;
  };

  template<class T>
  class GLTree
  {
  public:
    GLTree(){}

    //! return the node associated at key;
    //    TreeNode<T> *node(const QString &key) const
    //    {
    //      for(auto &v : m_node)
    //        if(v->key() == key)
    //          return v.get();
    //      return nullptr;
    //    }
    //! add a child node to node
    TreeNode<T> *addNode(const QString &key)
    {
      if(!m_node.empty())
        {
          for(auto &v : m_node)
            {
              if(v->key() == key)//node already exist
                return v.get();
            }
          auto node = std::make_shared<TreeNode<T>>(key);
          m_node.push_back(node);
          return node.get();
        }
      else
        {
          auto node = std::make_shared<TreeNode<T>>(key);
          m_node.push_back(node);
          return node.get();
        }
    }

    std::vector<std::shared_ptr<TreeNode<T> > > nodes() const{return m_node;}

  private:
    std::vector<std::shared_ptr<TreeNode<T>>> m_node;
  };

} // namespace GLHeaderGen

#endif // GLHEADERGEN_GLTREE_H
