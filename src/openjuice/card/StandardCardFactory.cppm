/**
 * @file StandardCardFactory.cppm
 * @module openjuice.card:StandardCardFactory
 * @brief Implementation of the StandardCardFactory class.
 *
 * This file contains the implementation of the StandardCardFactory class, which is used to create StandardCard objects.
 */

module;

#include "Macros.hpp"

export module openjuice.card:StandardCardFactory;

import std;
import stdx;

import openjuice.engine.card;
import openjuice.engine.managers;
import openjuice.card.standard;

using std::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

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
            case Dash::ID:
                return std::mem::make_shared<Dash>();
            case SakisCookie::ID:
                return std::mem::make_shared<SakisCookie>();
            case FlipOut::ID:
                return std::mem::make_shared<FlipOut>();
            case NiceJingle::ID:
                return std::mem::make_shared<NiceJingle>();
            case NicePresent::ID:
                return std::mem::make_shared<NicePresent>();
            case Pudding::ID:
                return std::mem::make_shared<Pudding>();
            case ImOnFire::ID:
                return std::mem::make_shared<ImOnFire>();
            case Rbits::ID:
                return std::mem::make_shared<Rbits>();
            case RainbowColoredCircle::ID:
                return std::mem::make_shared<RainbowColoredCircle>();
            case FinalBattle::ID:
                return std::mem::make_shared<FinalBattle>();
            case BadPudding::ID:
                return std::mem::make_shared<BadPudding>();
            case MimyuusHammer::ID:
                return std::mem::make_shared<MimyuusHammer>();
            case DangerousPudding::ID:
                return std::mem::make_shared<DangerousPudding>();
            case Assault::ID:
                return std::mem::make_shared<Assault>();
            case SkyRestaurantPures::ID:
                return std::mem::make_shared<SkyRestaurantPures>();
            case HereAndThere::ID:
                return std::mem::make_shared<HereAndThere>();
            case HolyNight::ID:
                return std::mem::make_shared<HolyNight>();
            case OutOfAmmo::ID:
                return std::mem::make_shared<OutOfAmmo>();
            case GiftExchange::ID:
                return std::mem::make_shared<GiftExchange>();
            case LittleWar::ID:
                return std::mem::make_shared<LittleWar>();
            // === Expansion Pack cards ===
            case LongDistanceShot::ID:
                return std::mem::make_shared<LongDistanceShot>();
            case StiffCrystal::ID:
                return std::mem::make_shared<StiffCrystal>();
            case Extend::ID:
                return std::mem::make_shared<Extend>();
            case PrincesssPrivilege::ID:
                return std::mem::make_shared<PrincesssPrivilege>();
            case BigMagnum::ID:
                return std::mem::make_shared<BigMagnum>();
            case Shield::ID:
                return std::mem::make_shared<Shield>();
            case ReverseAttributeField::ID:
                return std::mem::make_shared<ReverseAttributeField>();
            case PiggyBank::ID:
                return std::mem::make_shared<PiggyBank>();
            case Invasion::ID:
                return std::mem::make_shared<Invasion>();
            case GoAway::ID:
                return std::mem::make_shared<GoAway>();
            case Heat300::ID:
                return std::mem::make_shared<Heat300>();
            case TragedyInTheDeadOfNight::ID:
                return std::mem::make_shared<TragedyInTheDeadOfNight>();
            case Exchange::ID:
                return std::mem::make_shared<Exchange>();
            case Flamethrower::ID:
                return std::mem::make_shared<Flamethrower>();
            case ForTheFutureOfTheToyStore::ID:
                return std::mem::make_shared<ForTheFutureOfTheToyStore>();
            case CloudOfSeagulls::ID:
                return std::mem::make_shared<CloudOfSeagulls>();
            case WeAreWaruda::ID:
                return std::mem::make_shared<WeAreWaruda>();
            case Dinner::ID:
                return std::mem::make_shared<Dinner>();
            case SuperAllOutMode::ID:
                return std::mem::make_shared<SuperAllOutMode>();
            case ForcedRevival::ID:
                return std::mem::make_shared<ForcedRevival>();
            case OhMyFriend::ID:
                return std::mem::make_shared<OhMyFriend>();
            case SealedGuardian::ID:
                return std::mem::make_shared<SealedGuardian>();
            // === Mixed Booster Pack cards ===
            case LonelyChariot::ID:
                return std::mem::make_shared<LonelyChariot>();
            case Ambush::ID:
                return std::mem::make_shared<Ambush>();
            case PassionateResearch::ID:
                return std::mem::make_shared<PassionateResearch>();
            case PresidentsPrivilege::ID:
                return std::mem::make_shared<PresidentsPrivilege>();
            case Mimic::ID:
                return std::mem::make_shared<Mimic>();
            case TacticalRetreat::ID:
                return std::mem::make_shared<TacticalRetreat>();
            case ShieldCounter::ID:
                return std::mem::make_shared<ShieldCounter>();
            case PiyopiyoProcession::ID:
                return std::mem::make_shared<PiyopiyoProcession>();
            case SealedMemories::ID:
                return std::mem::make_shared<SealedMemories>();
            case MixPhenomenon::ID:
                return std::mem::make_shared<MixPhenomenon>();
            case ScarySolicitation::ID:
                return std::mem::make_shared<ScarySolicitation>();
            // === Acceleration Pack cards ===
            case CompletionReward::ID:
                return std::mem::make_shared<CompletionReward>();
            case GentlemansBattle::ID:
                return std::mem::make_shared<GentlemansBattle>();
            case AccelHyper::ID:
                return std::mem::make_shared<AccelHyper>();
            case Extension::ID:
                return std::mem::make_shared<Extension>();
            case QuickRestoration::ID:
                return std::mem::make_shared<QuickRestoration>();
            case BrutalPrank::ID:
                return std::mem::make_shared<BrutalPrank>();
            case PresentThief::ID:
                return std::mem::make_shared<PresentThief>();
            case PlayOfTheGods::ID:
                return std::mem::make_shared<PlayOfTheGods>();
            case ScrambledEve::ID:
                return std::mem::make_shared<ScrambledEve>();
            case StarBlastingLight::ID:
                return std::mem::make_shared<StarBlastingLight>();
            case UnluckyCharm::ID:
                return std::mem::make_shared<UnluckyCharm>();
            case WindyEnchantment::ID:
                return std::mem::make_shared<WindyEnchantment>();
            // // === Community Pack 1 cards ===
            // case TreasureThief::ID:
            //     return std::mem::make_shared<TreasureThief>();
            // case DarkSideOfBusiness::ID:
            //     return std::mem::make_shared<DarkSideOfBusiness>();
            // case Wanted::ID:
            //     return std::mem::make_shared<Wanted>();
            // case PartyTime::ID:
            //     return std::mem::make_shared<PartyTime>();
            // case LostChild::ID:
            //     return std::mem::make_shared<LostChild>();
            // case PriceOfPower::ID:
            //     return std::mem::make_shared<PriceOfPower>();
            // /// === Community Pack 2 cards ===
            // case PathBlockers::ID:
            //     return std::mem::make_shared<PathBlockers>();
            // case DesperateModification::ID:
            //     return std::mem::make_shared<DesperateModification>();
            // case Poppoformation::ID:
            //     return std::mem::make_shared<Poppoformation>();
            // case AcceleratingSky::ID:
            //     return std::mem::make_shared<AcceleratingSky>();
            // case PoppoTheSnatcher::ID:
            //     return std::mem::make_shared<PoppoTheSnatcher>();
            // case Bloodlust::ID:
            //     return std::mem::make_shared<Bloodlust>();
            // // === Pudding Pack cards ===
            // case BackdoorTrade::ID:
            //     return std::mem::make_shared<BackdoorTrade>();
            // case SinkOrSwim::ID:
            //     return std::mem::make_shared<SinkOrSwim>();
            // case SeriousBattle::ID:
            //     return std::mem::make_shared<SeriousBattle>();
            // case PortablePudding::ID:
            //     return std::mem::make_shared<PortablePudding>();
            // case IWannaSeeYou::ID:
            //     return std::mem::make_shared<IWannaSeeYou>();
            // case Encore::ID:
            //     return std::mem::make_shared<Encore>();
            // case SweetDestroyer::ID:
            //     return std::mem::make_shared<SweetDestroyer>();
            // case SereneHush::ID:
            //     return std::mem::make_shared<SereneHush>();
            // case UnpaidWork::ID:
            //     return std::mem::make_shared<UnpaidWork>();
            // case IndiscriminateFireSupport::ID:
            //     return std::mem::make_shared<IndiscriminateFireSupport>();
            // case LuckyCharm::ID:
            //     return std::mem::make_shared<LuckyCharm>();
            // case MetallicMonocoque::ID:
            //     return std::mem::make_shared<MetallicMonocoque>();
            // // === Community Pack 3 cards ===
            // case Overtime::ID:
            //     return std::mem::make_shared<Overtime>();
            // case DeceptiveDisarming::ID:
            //     return std::mem::make_shared<DeceptiveDisarming>();
            // case BanaNana::ID:
            //     return std::mem::make_shared<BanaNana>();
            // case PetSnacks::ID:
            //     return std::mem::make_shared<PetSnacks>();
            // case HomeImprovement::ID:
            //     return std::mem::make_shared<HomeImprovement>();
            // case LuckySevens::ID:
            //     return std::mem::make_shared<LuckySevens>();
            // // === Community Pack 4 cards ===
            // case WarpControl::ID:
            //     return std::mem::make_shared<WarpControl>();
            // case MyWildFriends::ID:
            //     return std::mem::make_shared<MyWildFriends>();
            // case ContestOfCuteness::ID:
            //     return std::mem::make_shared<ContestOfCuteness>();
            // case BankOfPoppo::ID:
            //     return std::mem::make_shared<BankOfPoppo>();
            // case Rebellion::ID:
            //     return std::mem::make_shared<Rebellion>();
            // case NanakosBit::ID:
            //     return std::mem::make_shared<NanakosBit>();
            // // === Extracurricular Pack cards ===
            // case FullBurst::ID:
            //     return std::mem::make_shared<FullBurst>();
            // case ChefsSpecial::ID:
            //     return std::mem::make_shared<ChefsSpecial>();
            // case GoWithTheFlow::ID:
            //     return std::mem::make_shared<GoWithTheFlow>();
            // case MousseTheThief::ID:
            //     return std::mem::make_shared<MousseTheThief>();
            // case ComingBackStronger::ID:
            //     return std::mem::make_shared<ComingBackStronger>();
            // case ExtremeAlteration::ID:
            //     return std::mem::make_shared<ExtremeAlteration>();
            // case TheGreatestTroublemakerEver::ID:
            //     return std::mem::make_shared<TheGreatestTroublemakerEver>();
            // case LookHowLongMyArmsAndLegsAreNow::ID:
            //     return std::mem::make_shared<LookHowLongMyArmsAndLegsAreNow>();
            // case WereTickedOff::ID:
            //     return std::mem::make_shared<WereTickedOff>();
            // case ProtectionFee::ID:
            //     return std::mem::make_shared<ProtectionFee>();
            // case FluffyAndFuzzy::ID:
            //     return std::mem::make_shared<FluffyAndFuzzy>();
            // case FeelTheRushWithAnEnergyDrink::ID:
            //     return std::mem::make_shared<FeelTheRushWithAnEnergyDrink>();

            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
