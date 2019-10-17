#ifndef __BKE_MULTI_FUNCTION_NETWORK_H__
#define __BKE_MULTI_FUNCTION_NETWORK_H__

#include "BKE_multi_function.h"

#include "BLI_optional.h"

namespace BKE {

using BLI::Optional;

namespace MultiFunctionNetwork {

class Node;
class FunctionNode;
class PlaceholderNode;

class Socket;
class InputSocket;
class OutputSocket;

class Network;

class Node {
 public:
  Network &network();

  ArrayRef<MultiFunctionDataType> input_types();
  ArrayRef<MultiFunctionDataType> output_types();

  bool is_function();
  bool is_placeholder();

  FunctionNode &as_function();
  PlaceholderNode &as_placeholder();
};

class FunctionNode : public Node {
 public:
  MultiFunction &function();
};

class PlaceholderNode : public Node {
};

class Socket {
 public:
  Node &node();
  MultiFunctionDataType &type();

  bool is_input();
  bool is_output();

  InputSocket &as_input();
  OutputSocket &as_output();
};

class InputSocket : public Socket {
 public:
  OutputSocket &origin();
};

class OutputSocket : public Socket {
 public:
  ArrayRef<InputSocket *> targets();
};

class Network {
 public:
};

/* Builder
 ****************************************/

class BuilderNode;
class BuilderFunctionNode;
class BuilderPlaceholderNode;

class BuilderSocket;
class BuilderInputSocket;
class BuilderOutputSocket;

class BuilderNetwork;

class BuilderNode {
 protected:
  BuilderNetwork *m_network;
  Vector<BuilderInputSocket *> m_inputs;
  Vector<BuilderOutputSocket *> m_outputs;
  bool m_is_placeholder;

  friend BuilderNetwork;

 public:
  BuilderNetwork &network();

  ArrayRef<BuilderInputSocket *> inputs();
  ArrayRef<BuilderOutputSocket *> outputs();

  bool is_function();
  bool is_placeholder();

  BuilderFunctionNode &as_function();
  BuilderPlaceholderNode &as_placeholder();
};

class BuilderFunctionNode : public BuilderNode {
 private:
  MultiFunction *m_function;
  Vector<uint> m_input_param_indices;
  Vector<uint> m_output_param_indices;

  friend BuilderNetwork;

 public:
  MultiFunction &function();
};

class BuilderPlaceholderNode : public BuilderNode {
};

class BuilderSocket {
 private:
  BuilderNode *m_node;
  bool m_is_output;
  uint m_index;
  MultiFunctionDataType m_type;

  friend BuilderNetwork;

 public:
  BuilderNode &node();
  MultiFunctionDataType type();

  bool is_input();
  bool is_output();

  BuilderInputSocket &as_input();
  BuilderOutputSocket &as_output();
};

class BuilderInputSocket : public BuilderSocket {
 private:
  BuilderOutputSocket *m_origin;

  friend BuilderNetwork;

 public:
  BuilderOutputSocket *origin();
};

class BuilderOutputSocket : public BuilderSocket {
 private:
  Vector<BuilderInputSocket *> m_targets;

  friend BuilderNetwork;

 public:
  ArrayRef<BuilderInputSocket *> targets();
};

class BuilderNetwork {
 private:
  Vector<std::unique_ptr<BuilderFunctionNode>> m_function_nodes;
  Vector<std::unique_ptr<BuilderPlaceholderNode>> m_placeholder_nodes;
  Vector<std::unique_ptr<BuilderInputSocket>> m_input_sockets;
  Vector<std::unique_ptr<BuilderOutputSocket>> m_output_sockets;

 public:
  BuilderFunctionNode &add_function(MultiFunction &function,
                                    ArrayRef<uint> input_param_indices,
                                    ArrayRef<uint> output_param_indices);
  BuilderPlaceholderNode &add_placeholder(ArrayRef<MultiFunctionDataType> input_types,
                                          ArrayRef<MultiFunctionDataType> output_types);
  void add_link(BuilderOutputSocket &from, BuilderInputSocket &to);
};

/* BuilderNode Implementations
 *******************************************/

BuilderNetwork &BuilderNode::network()
{
  return *m_network;
}

ArrayRef<BuilderInputSocket *> BuilderNode::inputs()
{
  return m_inputs;
}
ArrayRef<BuilderOutputSocket *> BuilderNode::outputs()
{
  return m_outputs;
}

bool BuilderNode::is_function()
{
  return !m_is_placeholder;
}
bool BuilderNode::is_placeholder()
{
  return m_is_placeholder;
}

BuilderFunctionNode &BuilderNode::as_function()
{
  BLI_assert(this->is_function());
  return *(BuilderFunctionNode *)this;
}
BuilderPlaceholderNode &BuilderNode::as_placeholder()
{
  BLI_assert(this->is_placeholder());
  return *(BuilderPlaceholderNode *)this;
}

/* BuilderFunctionNode Implementations
 *******************************************/

MultiFunction &BuilderFunctionNode::function()
{
  return *m_function;
}

/* BuilderSocket Implementations
 *******************************************/

BuilderNode &BuilderSocket::node()
{
  return *m_node;
}

MultiFunctionDataType BuilderSocket::type()
{
  return m_type;
}

bool BuilderSocket::is_input()
{
  return !m_is_output;
}
bool BuilderSocket::is_output()
{
  return m_is_output;
}

BuilderInputSocket &BuilderSocket::as_input()
{
  BLI_assert(this->is_input());
  return *(BuilderInputSocket *)this;
}
BuilderOutputSocket &BuilderSocket::as_output()
{
  BLI_assert(this->is_output());
  return *(BuilderOutputSocket *)this;
}

/* BuilderInputSocket Implementations
 *******************************************/

BuilderOutputSocket *BuilderInputSocket::origin()
{
  return m_origin;
}

/* BuilderOutputSocket Implementations
 *******************************************/

ArrayRef<BuilderInputSocket *> BuilderOutputSocket::targets()
{
  return m_targets;
}

}  // namespace MultiFunctionNetwork

}  // namespace BKE

#endif /* __BKE_MULTI_FUNCTION_NETWORK_H__ */
