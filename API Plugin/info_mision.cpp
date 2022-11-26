#include "info_mision.h"
#include "Utilities.h"

info_mision * info_mision::AllocateAndCreate()
{
	info_mision * a1 = (info_mision*)(Game::operator_new(0x50, "", 0x40));
	a1 = info_mision::Create(a1);
	return a1;
}
