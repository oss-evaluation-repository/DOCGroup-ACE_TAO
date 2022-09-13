#include "Basic.h"
#include "LB_server.h"

Basic::Basic (CORBA::Object_ptr object_group,
              CosLoadBalancing::LoadManager_ptr lm,
              CORBA::ORB_ptr orb,
              CORBA::Short num,
              const char *loc)
  : orb_ (CORBA::ORB::_duplicate (orb)),
    number_ (num)
{
  this->object_group_ = CORBA::Object::_duplicate (object_group);
  this->lm_ = CosLoadBalancing::LoadManager::_duplicate (lm);
  this->location_ = CORBA::string_dup (loc);
}

CORBA::Short
Basic::number ()
{
  return this->number_;
}

char *
Basic::get_string ()
{
  return CORBA::string_dup (this->location_);
}

void
Basic::remove_member ()
{
  try
    {
      PortableGroup::Location location (1);
      location.length (1);
      location[0].id = CORBA::string_dup (this->location_);
      this->lm_->remove_member (this->object_group_.in (),
                                location);

      ACE_DEBUG ((LM_DEBUG, "(%P|%t) - Removed Member at Location <%s>\n",
                      this->location_));
    }
  catch (const PortableGroup::ObjectNotFound& ex)
    {
      ex._tao_print_exception ("Caught exception in remove_member");
      throw CORBA::INTERNAL ();
    }
  catch (const PortableGroup::MemberNotFound& ex)
    {
      ex._tao_print_exception ("Caught exception in remove_member");
      throw CORBA::INTERNAL ();
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("Exception caught while destroying member\n");
    }

}

void
Basic::shutdown ()
{
  this->orb_->shutdown (false);
}
