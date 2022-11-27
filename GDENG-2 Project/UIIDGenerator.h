#pragma once
#include <cstdint>
#include <limits>
#include <vector>

using UIID = uint64_t;
// constexpr UIID UIIDMax = std::numeric_limits<UIID>::max();
// constexpr UIID UIIDError = 0;

class UIIDGenerator final
{
public:
	UIIDGenerator();
	~UIIDGenerator();
	
	// Check if the output is 0. As a 0 ID means failed due to reaching max EntityID count.
	UIID GenerateUIID();
	void AddReservedUIID(UIID idToReserve);
private:
	std::vector<UIID> m_ReservedUIIDList{};
	UIID m_CurrentUIIDToGenerate;
};

