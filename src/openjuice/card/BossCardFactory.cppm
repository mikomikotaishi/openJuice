/**
 * @file BossCardFactory.cppm
 * @module openjuice.card.BossCardFactory
 * @brief Implementation of the BossCardFactory class.
 *
 * This file contains the implementation of the BossCardFactory class, which is used to create BossCard objects.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.card.BossCardFactory;

import std;
import stdx;

import openjuice.engine.card.Card;
import openjuice.engine.card.SpawnTypes;
import openjuice.engine.managers.GlobalSettings;
import openjuice.card.boss;

using std::fmt::FormatContext;
using std::fmt::FormatParseContext;
using std::fmt::Formatter;
using std::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

namespace fmt = std::fmt;
namespace mem = std::mem;
namespace sys = std::sys;

using openjuice::engine::card::spawntypes::BossCard;

// using namespace openjuice::card::boss;
// using namespace openjuice::card::boss::hyper;

BEGIN_MODULE_NAMESPACE(openjuice::card);

/**
 * @class BossCardFactory
 * @brief Factory class for creating BossCard objects.
 *
 * The BossCardFactory class is a singleton factory class that creates BossCard objects based on the given ID.
 */
export class BossCardFactory final {
private:
    UTILITY_CLASS(BossCardFactory);

    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("BossCardFactory"); ///< The logger instance.
public:
    /** 
     * @enum SecondaryType
     * @brief The secondary type, used to specify to the factory what the ID is in relation to.
     */
    enum class SecondaryType: u8 {
        STANDARD, ///< A BossCard of standard variety
        HYPER ///< A BossCard of hyper variety
    };

    /**
     * @brief Create a BossCard object with the given ID.
     *
     * @param id ID of the BossCard to create
     * @return Shared pointer to the created BossCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<BossCard>> create(u8 id, SecondaryType type = SecondaryType::STANDARD) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating BossCard of ID: {}, secondary type: {}", id, type);
        #endif

        switch (type) {
            case SecondaryType::STANDARD:
                switch (id) {
                    case 0:
                        return nullptr;
                    // Big the Haruo's cards
                    // case 1:
                    //     return mem::make_shared<Doze>();
                    // case 2:
                    //     return mem::make_shared<GroupUp>();
                    // case 3:
                    //     return mem::make_shared<Peck>();
                    // case 4:
                    //     return mem::make_shared<Flight>();
                    // case 5:
                    //     return mem::make_shared<ChickenAttack>();
                    // case 6:
                    //     return mem::make_shared<PiyoMarch>();
                    // case 7:
                    //     return mem::make_shared<Regeneration>();
                    // case 8:
                    //     return mem::make_shared<Present>();
                    // case 9:
                    //     return mem::make_shared<HeadlessChicken>();
                    // case 10:
                    //     return mem::make_shared<CallOfTheChicken>();
                    // case 11:
                    //     return mem::make_shared<ChickenRun>();
                    // case 12:
                    //     return mem::make_shared<HenPecked>();
                    // case 13:
                    //     return mem::make_shared<SecondWing>();
                    // case 14:
                    //     return mem::make_shared<Swarm>();
                    // case 15:
                    //     return mem::make_shared<FinalWarning>();
                    // case 16:
                    //     return mem::make_shared<SavageTalons>();
                    // case 17:
                    //     return mem::make_shared<BeakOfTheGodbird>();
                    // M10 Robot's cards
                    // case 18:
                    //     return mem::make_shared<Malfunction>();
                    // case 19:
                    //     return mem::make_shared<QuickRepair>();
                    // case 20:
                    //     return mem::make_shared<BalanceCurrents>();
                    // case 21:
                    //     return mem::make_shared<ImmovableObject>();
                    // case 22:
                    //     return mem::make_shared<Turbo>();
                    // case 23:
                    //     return mem::make_shared<AssaultField>();
                    // case 24:
                    //     return mem::make_shared<EvasionDown>();
                    // case 25:
                    //     return mem::make_shared<RoboBeam>();
                    // case 26:
                    //     return mem::make_shared<DefenseDown>();
                    // case 27:
                    //     return mem::make_shared<Engage>();
                    // case 28:
                    //     return mem::make_shared<SelfDestruction>();
                    // case 29:
                    //     return mem::make_shared<HealthDown>();
                    // case 30:
                    //     return mem::make_shared<EMP>();
                    // case 31:
                    //     return mem::make_shared<SolidWitch>();
                    // case 32:
                    //     return mem::make_shared<AttackDown>();
                    // case 33:
                    //     return mem::make_shared<ImaginaryNumbers>();
                    // case 34:
                    //     return mem::make_shared<ScrambledDeltaField>();
                    // case 35:
                    //     return mem::make_shared<RecoveryMode>();
                    // Star Devourer's cards
                    // case 36:
                    //     return mem::make_shared<Nap>();
                    // case 37:
                    //     return mem::make_shared<Elusive>();
                    // case 38:
                    //     return mem::make_shared<StarMania>();
                    // case 39:
                    //     return mem::make_shared<PoppoTax>();
                    // case 40:
                    //     return mem::make_shared<Ubiquitous>();
                    // case 41:
                    //     return mem::make_shared<Snatcher>();
                    // case 42:
                    //     return mem::make_shared<SkyRestaurantPoppoEvent>();
                    // case 43:
                    //     return mem::make_shared<SkyRestaurantPoppoTrap>();
                    // case 44:
                    //     return mem::make_shared<HighwayRobbery>();
                    // case 45:
                    //     return mem::make_shared<Greed>();
                    // case 46:
                    //     return mem::make_shared<WarpPhenomenon>();
                    // case 47:
                    //     return mem::make_shared<Poppoformation>();
                    // case 48:
                    //     return mem::make_shared<Temptation>();
                    // case 49:
                    //     return mem::make_shared<PoppoGalaxy>();
                    // case 50:
                    //     return mem::make_shared<DeathAndTaxes>();
                    // case 51:
                    //     return mem::make_shared<ValueJudgement>();
                    // case 52:
                    //     return mem::make_shared<RansomNoteEvent>();
                    // case 53:
                    //     return mem::make_shared<RansomNoteGift>();
                    // case 54:
                    //     return mem::make_shared<Poppocalypse>();
                    // Summer Beast's cards
                    // case 55:
                    //     return mem::make_shared<Rest>();
                    // case 56:
                    //     return mem::make_shared<Chase>();
                    // case 57:
                    //     return mem::make_shared<Play>();
                    // case 58:
                    //     return mem::make_shared<TireOut>();
                    // case 59:
                    //     return mem::make_shared<PuddingSeeker>();
                    // case 60:
                    //     return mem::make_shared<Birds>();
                    // case 61:
                    //     return mem::make_shared<SeagullFriend>();
                    // case 62:
                    //     return mem::make_shared<DanceOfTheSeagulls>();
                    // case 63:
                    //     return mem::make_shared<PlayTag>();
                    // case 64:
                    //     return mem::make_shared<HideAndSeek>();
                    // case 65:
                    //     return mem::make_shared<SplashWater>();
                    // case 66:
                    //     return mem::make_shared<PsychedUp>();
                    // case 67:
                    //     return mem::make_shared<PlayWithBirds>();
                    // case 68:
                    //     return mem::make_shared<Exhaustion>();
                    // case 69:
                    //     return mem::make_shared<SeagullMaster>();
                    // case 70:
                    //     return mem::make_shared<WatermelonSplitting>();
                    // case 71:
                    //     return mem::make_shared<PuddingBreak>();
                    // case 72:
                    //     return mem::make_shared<HypeItUp>();
                    // case 73:
                    //     return mem::make_shared<SandwichThieves>();
                    // Big the Jonathan's cards
                    // case 74:
                    //     return mem::make_shared<Snacks>();
                    // case 75:
                    //     return mem::make_shared<Screech>();
                    // case 76:
                    //     return mem::make_shared<Rake>();
                    // case 77:
                    //     return mem::make_shared<CloudOfSeagulls>();
                    // case 78:
                    //     return mem::make_shared<Rush>();
                    // case 79:
                    //     return mem::make_shared<ChaseAround>();
                    // case 80:
                    //     return mem::make_shared<Quake>();
                    // case 81:
                    //     return mem::make_shared<AirRaid>();
                    // case 82:
                    //     return mem::make_shared<DoubleRush>();
                    // case 83:
                    //     return mem::make_shared<Swipe>();
                    // case 84:
                    //     return mem::make_shared<Hunt>();
                    // case 85:
                    //     return mem::make_shared<FalseHope>();
                    // case 86:
                    //     return mem::make_shared<Snatch>();
                    // case 87:
                    //     return mem::make_shared<AirStrike>();
                    // case 88:
                    //     return mem::make_shared<MegaRush>();
                    // case 89:
                    //     return mem::make_shared<Frantic>();
                    // case 90:
                    //     return mem::make_shared<WaveOfDespair>();
                    // case 91:
                    //     return mem::make_shared<AuraOfTerror>();
                    // RoPoChi's cards
                    // case 92:
                    //     return mem::make_shared<IdentityCrisis>();
                    // case 93:
                    //     return mem::make_shared<RoboTax>();
                    // case 94:
                    //     return mem::make_shared<Pluck>();
                    // case 95:
                    //     return mem::make_shared<Catcher>();
                    // case 96:
                    //     return mem::make_shared<BalanceCurrency>();
                    // case 97:
                    //     return mem::make_shared<PoppoMarch>();
                    // case 98:
                    //     return mem::make_shared<PremiumRegeneration>();
                    // case 99:
                    //     return mem::make_shared<WirelessChicken>();
                    // case 100:
                    //     return mem::make_shared<RoPoBarrage>();
                    // case 101:
                    //     return mem::make_shared<DelusionalNumbers>();
                    // case 102:
                    //     return mem::make_shared<SecondWing>();
                    // case 103:
                    //     return mem::make_shared<PoBomber>();
                    // case 104:
                    //     return mem::make_shared<InvisibleBomb>();
                    // case 105:
                    //     return mem::make_shared<TurboChicken>();
                    // case 106:
                    //     return mem::make_shared<PoppoUniverse>();
                    // case 107:
                    //     return mem::make_shared<Poppocare>();
                    // case 108:
                    //     return mem::make_shared<RefinedTalons>();
                    // case 109:
                    //     return mem::make_shared<BeakOfTheDemiBird>();
                    // case 110:
                    //     return mem::make_shared<BigPosSpecial>();
                    // Swimming Coach's cards
                    // case 111:
                    //     return mem::make_shared<Float>();
                    // case 112:
                    //     return mem::make_shared<Whirl>();
                    // case 113:
                    //     return mem::make_shared<BubbleBath>();
                    // case 114:
                    //     return mem::make_shared<EntryFee>();
                    // case 115:
                    //     return mem::make_shared<GulpOfWater>();
                    // case 116:
                    //     return mem::make_shared<Coaching>();
                    // case 117:
                    //     return mem::make_shared<Confiscate>();
                    // case 118:
                    //     return mem::make_shared<Shock>();
                    // case 119:
                    //     return mem::make_shared<GoFaster>();
                    // case 120:
                    //     return mem::make_shared<Respite>();
                    // case 121:
                    //     return mem::make_shared<PaceUp>();
                    // case 122:
                    //     return mem::make_shared<Hustle>();
                    // case 123:
                    //     return mem::make_shared<Motivate>();
                    // case 124:
                    //     return mem::make_shared<TropicalCyclone>();
                    // case 125:
                    //     return mem::make_shared<Butterfly>();
                    // case 126:
                    //     return mem::make_shared<Zap>();
                    // case 127:
                    //     return mem::make_shared<Encourage>();
                    // case 128:
                    //     return mem::make_shared<MovingTheGoalpost>();
                    default:
                        return nullopt;
                }
            case SecondaryType::HYPER:
                switch (id) {
                    case 0:
                        return nullptr;
                    // case 1:
                    //     return mem::make_shared<Roost>();
                    // case 2:
                    //     return mem::make_shared<HyperRoost>();
                    // case 3:
                    //     return mem::make_shared<Protect>();
                    // case 4:
                    //     return mem::make_shared<PerfectReflectiveShell>();
                    // case 5:
                    //     return mem::make_shared<FromTheAbyss>();
                    // case 6:
                    //     return mem::make_shared<HypeMode>();
                    // case 7:
                    //     return mem::make_shared<Rampage>();
                    // case 8:
                    //     return mem::make_shared<HyperRampage>();
                    // case 9:
                    //     return mem::make_shared<Launch>();
                    // case 10:
                    //     return mem::make_shared<Dive>();
                    // case 11:
                    //     return mem::make_shared<RoostBoost>();
                    // case 12:
                    //     return mem::make_shared<PoTect>();
                    // case 13:
                    //     return mem::make_shared<Goalpost>();
                    // case 14:
                    //     return mem::make_shared<BalloonJerk>();
                    // case 15:
                    //     return mem::make_shared<SwimmingRinger>();
                    // case 16:
                    //     return mem::make_shared<HomeSweeper>();
                    default:
                        return nullopt;
                }
            default:
                sys::unreachable();
        }
    }
};

END_MODULE_NAMESPACE();

using openjuice::card::BossCardFactory;

template <>
struct Formatter<BossCardFactory::SecondaryType> {
    static constexpr const char* parse(FormatParseContext& ctx) noexcept {
        return ctx.begin();
    }

    static FormatContext::Iterator format(BossCardFactory::SecondaryType type, FormatContext& ctx) {
        StringView name;
        switch (type) {
            case BossCardFactory::SecondaryType::STANDARD:
                name = "Standard";
                break;
            case BossCardFactory::SecondaryType::HYPER:
                name = "Hyper";
                break;
            default:
                sys::unreachable();
        }
        return fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(BossCardFactory::SecondaryType);
