/**
 * @file discordpp.cppm
 * @module discordpp
 * @brief Module file for Discord Social SDK operations.
 * @version 1.7.13357
 */

module;

#define DISCORDPP_IMPLEMENTATION
#include <discordpp/discordpp.h>

export module discordpp;

/**
 * @namespace discordpp
 * @brief The Discord discordpp:: namespace
 */
export namespace discordpp {
    using discordpp::DiscordObjectState;
    using discordpp::RunCallbacks;
    using discordpp::ActivityActionTypes;
    using discordpp::ActivityPartyPrivacy;
    using discordpp::ActivityTypes;
    using discordpp::StatusDisplayTypes;
    using discordpp::ActivityGamePlatforms;
    using discordpp::ErrorType;
    using discordpp::HttpStatusCode;
    using discordpp::AuthenticationCodeChallengeMethod;
    using discordpp::IntegrationType;
    using discordpp::ChannelType;
    using discordpp::AdditionalContentType;
    using discordpp::AudioSystem;
    using discordpp::AudioModeType;
    using discordpp::RelationshipType;
    using discordpp::ExternalIdentityProviderType;
    using discordpp::StatusType;
    using discordpp::DisclosureTypes;
    using discordpp::AuthorizationTokenType;
    using discordpp::AuthenticationExternalAuthType;
    using discordpp::LoggingSeverity;
    using discordpp::RelationshipGroupType;
    using discordpp::ActivityInvite;
    using discordpp::ActivityAssets;
    using discordpp::ActivityTimestamps;
    using discordpp::ActivityParty;
    using discordpp::ActivitySecrets;
    using discordpp::ActivityButton;
    using discordpp::Activity;
    using discordpp::ClientResult;
    using discordpp::AuthorizationCodeChallenge;
    using discordpp::AuthorizationCodeVerifier;
    using discordpp::AuthorizationArgs;
    using discordpp::DeviceAuthorizationArgs;
    using discordpp::VoiceStateHandle;
    using discordpp::VADThresholdSettings;
    using discordpp::Call;
    using discordpp::ChannelHandle;
    using discordpp::GuildMinimal;
    using discordpp::GuildChannel;
    using discordpp::LinkedLobby;
    using discordpp::LinkedChannel;
    using discordpp::RelationshipHandle;
    using discordpp::UserApplicationProfileHandle;
    using discordpp::UserHandle;
    using discordpp::LobbyMemberHandle;
    using discordpp::LobbyHandle;
    using discordpp::AdditionalContent;
    using discordpp::MessageHandle;
    using discordpp::AudioDevice;
    using discordpp::UserMessageSummary;
    using discordpp::ClientCreateOptions;
    using discordpp::Client;
    using discordpp::CallInfoHandle;

    using discordpp::EnumToString;
    
    using discordpp::HasSynchronizationContext;
    using discordpp::PostTask;
    using discordpp::SetSynchronizationContext;
    
    using discordpp::TDelegateUserData;

    using discordpp::ConvertedProperties;
    using discordpp::ConvertReturnedProperties;
}
