#ifndef CUKEBINS_STEPMACROS_HPP_
#define CUKEBINS_STEPMACROS_HPP_

#include "../RegistrationMacros.hpp"

// ************************************************************************** //
// **************                     STEP                     ************** //
// ************************************************************************** //

#define CUKE_STEP_(step_matcher)                        \
CUKE_STEP_WITH_NAME_(CUKE_GEN_OBJECT_NAME_, step_matcher) \
/**/

#define CUKE_STEP_WITH_NAME_(step_name, step_matcher) \
CUKE_OBJECT_(                                         \
    step_name,                                        \
    STEP_INHERITANCE(step_name),                      \
    CUKE_STEP_REGISTRATION_(step_name, step_matcher)  \
)                                                     \
/**/

#define CUKE_STEP_REGISTRATION_(step_name, step_matcher)      \
::cukebins::internal::registerStep< step_name >(step_matcher) \
/**/

// ************************************************************************** //
// **************               GIVEN/WHEN/THEN                ************** //
// ************************************************************************** //

#define GIVEN CUKE_STEP_
#define WHEN CUKE_STEP_
#define THEN CUKE_STEP_

// ************************************************************************** //
// **************                 REGEX_PARAM                  ************** //
// ************************************************************************** //

#define REGEX_PARAM(type, name) type name(getInvokeArg<type>())

// ************************************************************************** //
// **************                USING_CONTEXT                 ************** //
// ************************************************************************** //

#define USING_CONTEXT(type, name) ::cukebins::internal::SessionContextPtr<type> name

#endif /* CUKEBINS_STEPMACROS_HPP_ */
