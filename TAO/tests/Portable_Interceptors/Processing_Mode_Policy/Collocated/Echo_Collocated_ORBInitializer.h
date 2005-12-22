// -*- C++ -*-
//
// $Id$

#ifndef TAO_ECHO_CLIENT_ORB_INITIALIZER_H
#define TAO_ECHO_CLIENT_ORB_INITIALIZER_H

#include /**/ "ace/pre.h"

#include "tao/orbconf.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/PI/PI.h"
#include "tao/PI/ProcessingModePolicyC.h"
#include "tao/LocalObject.h"

// This is to remove "inherits via dominance" warnings from MSVC.
// MSVC is being a little too paranoid.
#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

/// Echo client ORB initializer.
class Echo_Collocated_ORBInitializer :
  public virtual PortableInterceptor::ORBInitializer,
  public virtual TAO_Local_RefCounted_Object
{
public:

  Echo_Collocated_ORBInitializer
    (PortableInterceptor::ProcessingMode server_proc_mode,
     PortableInterceptor::ProcessingMode client_proc_mode);

  virtual void pre_init (PortableInterceptor::ORBInitInfo_ptr info
                         ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void post_init (PortableInterceptor::ORBInitInfo_ptr info
                          ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException));

private:

  PortableInterceptor::ProcessingMode server_processing_mode_;
  PortableInterceptor::ProcessingMode client_processing_mode_;
};

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */


#include /**/ "ace/post.h"

#endif /* TAO_ECHO_CLIENT_ORB_INITIALIZER_H */
