//
// $Id$
//
/* -*- c++ -*- */
// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    be_visitor_component_scope.h
//
// = DESCRIPTION
//    Base class for visitors that need to visit the scope of a 
//    component and its ancestors, if any.
//
// = AUTHOR
//    Jeff Parsons
//
// ============================================================================

#ifndef _BE_COMPONENT_COMPONENT_SCOPE_H_
#define _BE_COMPONENT_COMPONENT_SCOPE_H_

#include "ace/SString.h"

#include "be_visitor_scope.h"

class be_visitor_component_scope : public be_visitor_scope
{
  //
  // = TITLE
  //   be_visitor_component_scope
  //
  // = DESCRIPTION
  //   This is an abstract visitor providing a scope visitation
  //   method that traverses the base component recursively.
  //
protected:
  be_visitor_component_scope (be_visitor_context *ctx);
  
  virtual ~be_visitor_component_scope (void);
  
public:
  virtual int visit_extended_port (be_extended_port *node);
  virtual int visit_mirror_port (be_mirror_port *node);

  // Automatically recurses to the ancestor scopes, if any.
  int visit_component_scope (be_component *node);
  
  // These two methods are used instead of overriding
  // visit_porttype so we can traverse a porttype only
  // when it is referenced.
  
  int visit_porttype_scope (be_porttype *node);

  // Swaps uses for provides members and vice versa.S 
  int visit_porttype_scope_mirror (be_porttype *node);
  
  // This override is used to prefix a provides or uses
  // node's local name with the name of the port or
  // mirrorport node that may contain reference the
  // containing porttype.
  // TODO - support nested ports, if they are allowed.
  virtual int pre_process (be_decl *);
  
protected:
  void gen_svnt_entrypoint_decl (void);
  void gen_svnt_entrypoint_defn (void);
  void gen_exec_entrypoint_decl (void);
  void gen_exec_entrypoint_defn (void);
  
protected:
  be_component *node_;
  TAO_OutStream &os_;
  ACE_CString export_macro_;
  bool swapping_;
  bool static_config_;
  
private:
  ACE_CString current_port_name_;
};

#endif /* _BE_COMPONENT_COMPONENT_SCOPE_H_ */
