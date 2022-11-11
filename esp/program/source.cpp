#include "mem.h""
#include <thread>
namespace offsets 
{
	// client.dll
	constexpr ::std::ptrdiff_t dwLocalPlayer = 0xDE6964;
	constexpr ::std::ptrdiff_t dwEntityList = 0x4DFBE54;

	// entity
	constexpr ::std::ptrdiff_t m_iTeamNum = 0xF4;
	constexpr ::std::ptrdiff_t m_bSpotted = 0x93D;
}

int main() 
{
	auto mem = Memory("csgo.exe");
	const auto client = mem.GetModuleAddress("client.dll");

	while (true) 
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		const auto localPlayer = mem.Read<uintptr_t>(client + offsets::dwLocalPlayer);
		const auto localTeam = mem.Read<uintptr_t>(client + offsets::m_iTeamNum);

		for (auto i = 1; i <= 32; ++i)
		{
			const auto entity = mem.Read<std::uintptr_t>(client + offsets::dwEntityList + i * 0x10);

			if (mem.Read<std::uintptr_t>(entity + offsets::m_iTeamNum) == localTeam) continue;
		}

	}
	return 0;
}