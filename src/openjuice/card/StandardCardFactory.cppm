/**
 * @file StandardCardFactory.cppm
 * @module openjuice.card.StandardCardFactory
 * @brief Implementation of the StandardCardFactory class.
 *
 * This file contains the implementation of the StandardCardFactory class, which is used to create StandardCard objects.
 */

module;

#include "Macros.hpp"

export module openjuice.card.StandardCardFactory;

import std;
import stdx;

import openjuice.engine.card.Card;
import openjuice.engine.card.SpawnTypes;
import openjuice.engine.managers.GlobalSettings;
import openjuice.card.standard;

using std::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

namespace fmt = std::fmt;
namespace mem = std::mem;

using openjuice::engine::card::spawntypes::StandardCard;

using namespace openjuice::card::standard::acceleration;
using namespace openjuice::card::standard::base;
// using namespace openjuice::card::standard::community1;
// using namespace openjuice::card::standard::community2;
// using namespace openjuice::card::standard::community3;
// using namespace openjuice::card::standard::community4;
using namespace openjuice::card::standard::expansion;
// using namespace openjuice::card::standard::extracurricular;
using namespace openjuice::card::standard::mixedbooster;
// using namespace openjuice::card::standard::pudding;

BEGIN_MODULE_NAMESPACE(openjuice::card);

/**
 * @class StandardCardFactory
 * @brief Factory class for creating StandardCard objects.
 *
 * The StandardCardFactory class is a singleton factory class that creates StandardCard objects based on the given ID.
 */
export class StandardCardFactory final {
private:
    UTILITY_CLASS(StandardCardFactory);

    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("StandardCardFactory"); ///< The logger instance.
public:
    /**
     * @brief Create a StandardCard object with the given ID.
     *
     * @param id ID of the StandardCard to create
     * @return Shared pointer to the created StandardCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<StandardCard>> create(u16 id) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating StandardCard of ID: {}", id);
        #endif

        switch (id) {
            case 0:
                return nullptr;
            // === Base Pack cards ===
            case 1:
                return mem::make_shared<Dash>();
            case 2:
                return mem::make_shared<SakisCookie>();
            case 3:
                return mem::make_shared<FlipOut>();
            case 4:
                return mem::make_shared<NiceJingle>();
            case 5:
                return mem::make_shared<NicePresent>();
            case 6:
                return mem::make_shared<Pudding>();
            case 7:
                return mem::make_shared<ImOnFire>();
            case 8:
                return mem::make_shared<Rbits>();
            case 9:
                return mem::make_shared<RainbowColoredCircle>();
            case 10:
                return mem::make_shared<FinalBattle>();
            case 11:
                return mem::make_shared<BadPudding>();
            case 12:
                return mem::make_shared<MimyuusHammer>();
            case 13:
                return mem::make_shared<DangerousPudding>();
            case 14:
                return mem::make_shared<Assault>();
            case 15:
                return mem::make_shared<SkyRestaurantPures>();
            case 16:
                return mem::make_shared<HereAndThere>();
            case 17:
                return mem::make_shared<HolyNight>();
            case 18:
                return mem::make_shared<OutOfAmmo>();
            case 19:
                return mem::make_shared<GiftExchange>();
            case 20:
                return mem::make_shared<LittleWar>();
            // === Expansion Pack cards ===
            case 21:
                return mem::make_shared<LongDistanceShot>();
            case 22:
                return mem::make_shared<StiffCrystal>();
            case 23:
                return mem::make_shared<Extend>();
            case 24:
                return mem::make_shared<PrincesssPrivilege>();
            case 25:
                return mem::make_shared<BigMagnum>();
            case 26:
                return mem::make_shared<Shield>();
            case 27:
                return mem::make_shared<ReverseAttributeField>();
            case 28:
                return mem::make_shared<PiggyBank>();
            case 29:
                return mem::make_shared<Invasion>();
            case 30:
                return mem::make_shared<GoAway>();
            case 31:
                return mem::make_shared<Heat300>();
            case 32:
                return mem::make_shared<TragedyInTheDeadOfNight>();
            case 33:
                return mem::make_shared<Exchange>();
            case 34:
                return mem::make_shared<Flamethrower>();
            case 35:
                return mem::make_shared<ForTheFutureOfTheToyStore>();
            case 36:
                return mem::make_shared<CloudOfSeagulls>();
            case 37:
                return mem::make_shared<WeAreWaruda>();
            case 38:
                return mem::make_shared<Dinner>();
            case 39:
                return mem::make_shared<SuperAllOutMode>();
            case 40:
                return mem::make_shared<ForcedRevival>();
            case 41:
                return mem::make_shared<OhMyFriend>();
            case 42:
                return mem::make_shared<SealedGuardian>();
            // === Mixed Booster Pack cards ===
            case 43:
                return mem::make_shared<LonelyChariot>();
            case 44:
                return mem::make_shared<Ambush>();
            case 45:
                return mem::make_shared<PassionateResearch>();
            case 46:
                return mem::make_shared<PresidentsPrivilege>();
            case 47:
                return mem::make_shared<Mimic>();
            case 48:
                return mem::make_shared<TacticalRetreat>();
            case 49:
                return mem::make_shared<ShieldCounter>();
            case 50:
                return mem::make_shared<PiyopiyoProcession>();
            case 51:
                return mem::make_shared<SealedMemories>();
            case 52:
                return mem::make_shared<MixPhenomenon>();
            case 53:
                return mem::make_shared<ScarySolicitation>();
            // === Acceleration Pack cards ===
            case 54:
                return mem::make_shared<CompletionReward>();
            case 55:
                return mem::make_shared<GentlemansBattle>();
            case 56:
                return mem::make_shared<AccelHyper>();
            case 57:
                return mem::make_shared<Extension>();
            case 58:
                return mem::make_shared<QuickRestoration>();
            case 59:
                return mem::make_shared<BrutalPrank>();
            case 60:
                return mem::make_shared<PresentThief>();
            case 61:
                return mem::make_shared<PlayOfTheGods>();
            case 62:
                return mem::make_shared<ScrambledEve>();
            case 63:
                return mem::make_shared<StarBlastingLight>();
            case 64:
                return mem::make_shared<UnluckyCharm>();
            case 65:
                return mem::make_shared<WindyEnchantment>();
            // // === Community Pack 1 cards ===
            // case 66:
            //     return mem::make_shared<TreasureThief>();
            // case 67:
            //     return mem::make_shared<DarkSideOfBusiness>();
            // case 68:
            //     return mem::make_shared<Wanted>();
            // case 69:
            //     return mem::make_shared<PartyTime>();
            // case 70:
            //     return mem::make_shared<LostChild>();
            // case 71:
            //     return mem::make_shared<PriceOfPower>();
            // /// === Community Pack 2 cards ===
            // case 72:
            //     return mem::make_shared<PathBlockers>();
            // case 73:
            //     return mem::make_shared<DesperateModification>();
            // case 74:
            //     return mem::make_shared<Poppoformation>();
            // case 75:
            //     return mem::make_shared<AcceleratingSky>();
            // case 76:
            //     return mem::make_shared<PoppoTheSnatcher>();
            // case 77:
            //     return mem::make_shared<Bloodlust>();
            // // === Pudding Pack cards ===
            // case 78:
            //     return mem::make_shared<BackdoorTrade>();
            // case 79:
            //     return mem::make_shared<SinkOrSwim>();
            // case 80:
            //     return mem::make_shared<SeriousBattle>();
            // case 81:
            //     return mem::make_shared<PortablePudding>();
            // case 82:
            //     return mem::make_shared<IWannaSeeYou>();
            // case 83:
            //     return mem::make_shared<Encore>();
            // case 84:
            //     return mem::make_shared<SweetDestroyer>();
            // case 85:
            //     return mem::make_shared<SereneHush>();
            // case 86:
            //     return mem::make_shared<UnpaidWork>();
            // case 87:
            //     return mem::make_shared<IndiscriminateFireSupport>();
            // case 88:
            //     return mem::make_shared<LuckyCharm>();
            // case 89:
            //     return mem::make_shared<MetallicMonocoque>();
            // // === Community Pack 3 cards ===
            // case 90:
            //     return mem::make_shared<Overtime>();
            // case 91:
            //     return mem::make_shared<DeceptiveDisarming>();
            // case 92:
            //     return mem::make_shared<BanaNana>();
            // case 93:
            //     return mem::make_shared<PetSnacks>();
            // case 94:
            //     return mem::make_shared<HomeImprovement>();
            // case 95:
            //     return mem::make_shared<LuckySevens>();
            // // === Community Pack 4 cards ===
            // case 96:
            //     return mem::make_shared<WarpControl>();
            // case 97:
            //     return mem::make_shared<MyWildFriends>();
            // case 98:
            //     return mem::make_shared<ContestOfCuteness>();
            // case 99:
            //     return mem::make_shared<BankOfPoppo>();
            // case 100:
            //     return mem::make_shared<Rebellion>();
            // case 101:
            //     return mem::make_shared<NanakosBit>();
            // // === Extracurricular Pack cards ===
            // case 102:
            //     return mem::make_shared<FullBurst>();
            // case 103:
            //     return mem::make_shared<ChefsSpecial>();
            // case 104:
            //     return mem::make_shared<GoWithTheFlow>();
            // case 105:
            //     return mem::make_shared<MousseTheThief>();
            // case 106:
            //     return mem::make_shared<ComingBackStronger>();
            // case 107:
            //     return mem::make_shared<ExtremeAlteration>();
            // case 108:
            //     return mem::make_shared<TheGreatestTroublemakerEver>();
            // case 109:
            //     return mem::make_shared<LookHowLongMyArmsAndLegsAreNow>();
            // case 110:
            //     return mem::make_shared<WereTickedOff>();
            // case 111:
            //     return mem::make_shared<ProtectionFee>();
            // case 112:
            //     return mem::make_shared<FluffyAndFuzzy>();
            // case 113:
            //     return mem::make_shared<FeelTheRushWithAnEnergyDrink>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
