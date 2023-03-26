#include <example/network.h>

extern struct string string;

inline uintptr_t create_packet(int type)
{
	uintptr_t pkt[2];
	TMCALL("?createPacket@MinecraftPackets@@SA?AV?$shared_ptr@VPacket@@@std@@W4MinecraftPacketIds@@@Z",
        void (*)(uintptr_t [2], int),
		pkt, type);
	return *pkt;
}

inline void send_network_packet(struct player *player, uintptr_t pkt)
{
	TMCALL("?sendNetworkPacket@ServerPlayer@@UEBAXAEAVPacket@@@Z",
        void (*)(struct player *player, uintptr_t pkt),
		player, pkt);
}

void send_play_sound_packet(struct player *player, const char *sound_name,
			 				struct vec3 pos, float volume, float pitch)
{
	uintptr_t pkt = create_packet(86);

	// Never dereference struct string.
	// Please use functions like memcpy to manipulate data
	struct string *sound_name_cpp_str = string.string(sound_name);
	memcpy((void *)(pkt + 48), sound_name_cpp_str, 32);

	DEREFERENCE(int, pkt, 80) = (int)(pos.x * 8.0F);
	DEREFERENCE(int, pkt, 84) = (int)(pos.y * 8.0F);
	DEREFERENCE(int, pkt, 88) = (int)(pos.z * 8.0F);
	DEREFERENCE(float, pkt, 92) = volume;
	DEREFERENCE(float, pkt, 96) = pitch;
	send_network_packet(player, pkt);
	free(sound_name_cpp_str);
}
