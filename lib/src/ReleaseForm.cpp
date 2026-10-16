#include "ReleaseForm.h"

ReleaseForm::ReleaseForm(const std::string &formName) : formName(formName) {}

const std::string &ReleaseForm::getFormName() const noexcept
{
    return formName;
}
