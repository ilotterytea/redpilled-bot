#pragma once

#include "CommandLoader.h"
#include "client/twitch.h"
#include "client/twitch_message.h"

void handle_chat_message(TwitchIRCClient *client, CommandLoader *commandLoader,
                         IRCMessage<IRCMessageType::PrivmsgMessage> message);
