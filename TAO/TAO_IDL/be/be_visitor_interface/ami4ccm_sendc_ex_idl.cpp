
//=============================================================================
/**
 *  @file    ami4ccm_sendc_ex_idl.cpp
 *
 *  $Id$
 *
 *  Visitor generating code for AMI4CCM Interfaces in the executor IDL
 *
 *
 *  @author Jeff Parsons
 */
//=============================================================================

be_visitor_ami4ccm_sendc_ex_idl::be_visitor_ami4ccm_sendc_ex_idl (
      be_visitor_context *ctx)
  : be_visitor_scope (ctx),
    os_ (*ctx->stream ())
{
}

be_visitor_ami4ccm_sendc_ex_idl::~be_visitor_ami4ccm_sendc_ex_idl (void)
{
}

int
be_visitor_ami4ccm_sendc_ex_idl::visit_interface (be_interface *node)
{
  this->iface_ = node;

  os_ << be_nl << be_nl
      << "// TAO_IDL - Generated from" << be_nl
      << "// " << __FILE__ << ":" << __LINE__;

  os_ << be_nl << be_nl
      << "local interface AMI_"
      << node->original_local_name () << be_nl
      << "{" << be_idt;
      
  if (this->visit_scope (node) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("be_visitor_ami4ccm_sendc_ex_idl")
                         ACE_TEXT ("::visit_interface - ")
                         ACE_TEXT ("visit_scope() failed\n")),
                        -1);         
    }
  
  os_ << be_uidt_nl
      << "};";
      
  return 0;
}

int
be_visitor_ami4ccm_sendc_ex_idl::visit_operation (be_operation *node)
{
  if (node->flags () == AST_Operation::OP_oneway)
    {
      // We do nothing for oneways!
      return 0;
    }

  os_ << be_nl
      << "void sendc_" << node->original_local_name ()
      << " (" << be_idt_nl
      << "in AMI_" << this->iface_->original_local_name ()
      << "Callback ami_handler";
      
  if (this->visit_scope (node) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("be_visitor_ami4ccm_rh_ex_idl::visit_operation - ")
                         ACE_TEXT ("visit_scope() failed\n")),
                        -1);         
    }
      
  os_ << ");" << be_uidt;
  
  return 0;
}

int
be_visitor_ami4ccm_sendc_ex_idl::visit_attribute (be_attribute *node)
{
  this->gen_attr_sendc_ops (false, node);
  
  if (!node->readonly ())
    {
      this->gen_attr_sendc_ops (true, node);
    }
    
  return 0;
}

int
be_visitor_ami4ccm_sendc_ex_idl::visit_argument (be_argument *node)
{
  if (node->direction () != AST_Argument::dir_IN)
    {
      return 0;
    }
    
  be_type *t =
    be_type::narrow_from_decl (node->field_type ());
    
  os_ << be_nl
      << "in ";
  
  os_ << IdentifierHelper::type_name (t, this);
  
  os_ << " " << node->original_local_name ();
    
  return 0;
}

int
be_visitor_ami4ccm_sendc_ex_idl::visit_string (be_string *node)
{
  os_ << (node->width () > 1 ? "w" : "") << "string";

  ACE_CDR::ULong bound = node->max_size ()->ev ()->u.ulval;

  if (bound > 0)
    {
      os_ << "<" << bound << ">";
    }

  return 0;
}

int
be_visitor_ami4ccm_sendc_ex_idl::visit_sequence (be_sequence *node)
{
  // Keep output statements separate because of side effects.
  os_ << "sequence<";
  os_ << IdentifierHelper::type_name (node->base_type (), this);

  if (!node->unbounded ())
    {
      os_ << ", " << node->max_size ()->ev ()->u.ulval;
    }

  os_ << "> ";

  return 0;
}

int
be_visitor_ami4ccm_sendc_ex_idl::pre_process (be_decl *node)
{
  be_operation *op =
    be_operation::narrow_from_scope (this->ctx_->scope ());
    
  if (op != 0)
    {
      if (op->void_return_type () && this->elem_number () == 1)
        {
          return 0;
        }
    }
    
  be_argument *arg = be_argument::narrow_from_decl (node);
  
  if (arg == 0)
    {
      return 0;
    }
    
  if (arg->direction () != AST_Argument::dir_IN)
    {
      return 0;
    }

  os_ << ",";
    
  return 0;
}

void
be_visitor_ami4ccm_sendc_ex_idl::gen_attr_sendc_ops (
  bool is_set_op,
  be_attribute *node)
{
  os_ << be_nl
      << "void sendc_" << (is_set_op ? "set_" : "get_")
      << node->original_local_name () << " (" << be_idt_nl
      << "in AMI_" << this->iface_->original_local_name ()
      << "Callback ami_handler";
      
  if (is_set_op)
    {
      be_type *t =
        be_type::narrow_from_decl (node->field_type ());
        
      os_ << "," << be_nl << "in ";
      
      os_ << IdentifierHelper::type_name (t, this);
      
      os_ << " " << node->original_local_name ();
    }
    
  os_ << ");" << be_uidt;
}