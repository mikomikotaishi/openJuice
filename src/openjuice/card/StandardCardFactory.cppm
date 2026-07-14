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

import stdx;

import :standard;

import openjuice.engine.card;
import openjuice.engine.services;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;

using openjuice::engine::card::spawn::StandardCard;

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
public:
    StandardCardFactory() = delete("StandardCardFactory is a utility class and cannot be instantiated.");

    /**
     * @brief Create a StandardCard object with the given ID.
     * @param id ID of the StandardCard to create
     * @return Shared pointer to the created StandardCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static constexpr Optional<SharedPointer<StandardCard>> create(u16 id) noexcept {
        switch (id) {
            case 0:
                return nullptr;
            // === Base Pack cards ===
            case Dash::ID:
                return Pointers::shared<Dash>();
            case SakisCookie::ID:
                return Pointers::shared<SakisCookie>();
            case FlipOut::ID:
                return Pointers::shared<FlipOut>();
            case NiceJingle::ID:
                return Pointers::shared<NiceJingle>();
            case NicePresent::ID:
                return Pointers::shared<NicePresent>();
            case Pudding::ID:
                return Pointers::shared<Pudding>();
            case ImOnFire::ID:
                return Pointers::shared<ImOnFire>();
            case Rbits::ID:
                return Pointers::shared<Rbits>();
            case RainbowColoredCircle::ID:
                return Pointers::shared<RainbowColoredCircle>();
            case FinalBattle::ID:
                return Pointers::shared<FinalBattle>();
            case BadPudding::ID:
                return Pointers::shared<BadPudding>();
            case MimyuusHammer::ID:
                return Pointers::shared<MimyuusHammer>();
            case DangerousPudding::ID:
                return Pointers::shared<DangerousPudding>();
            case Assault::ID:
                return Pointers::shared<Assault>();
            case SkyRestaurantPures::ID:
                return Pointers::shared<SkyRestaurantPures>();
            case HereAndThere::ID:
                return Pointers::shared<HereAndThere>();
            case HolyNight::ID:
                return Pointers::shared<HolyNight>();
            case OutOfAmmo::ID:
                return Pointers::shared<OutOfAmmo>();
            case GiftExchange::ID:
                return Pointers::shared<GiftExchange>();
            case LittleWar::ID:
                return Pointers::shared<LittleWar>();
            // === Expansion Pack cards ===
            case LongDistanceShot::ID:
                return Pointers::shared<LongDistanceShot>();
            case StiffCrystal::ID:
                return Pointers::shared<StiffCrystal>();
            case Extend::ID:
                return Pointers::shared<Extend>();
            case PrincesssPrivilege::ID:
                return Pointers::shared<PrincesssPrivilege>();
            case BigMagnum::ID:
                return Pointers::shared<BigMagnum>();
            case Shield::ID:
                return Pointers::shared<Shield>();
            case ReverseAttributeField::ID:
                return Pointers::shared<ReverseAttributeField>();
            case PiggyBank::ID:
                return Pointers::shared<PiggyBank>();
            case Invasion::ID:
                return Pointers::shared<Invasion>();
            case GoAway::ID:
                return Pointers::shared<GoAway>();
            case Heat300::ID:
                return Pointers::shared<Heat300>();
            case TragedyInTheDeadOfNight::ID:
                return Pointers::shared<TragedyInTheDeadOfNight>();
            case Exchange::ID:
                return Pointers::shared<Exchange>();
            case Flamethrower::ID:
                return Pointers::shared<Flamethrower>();
            case ForTheFutureOfTheToyStore::ID:
                return Pointers::shared<ForTheFutureOfTheToyStore>();
            case CloudOfSeagulls::ID:
                return Pointers::shared<CloudOfSeagulls>();
            case WeAreWaruda::ID:
                return Pointers::shared<WeAreWaruda>();
            case Dinner::ID:
                return Pointers::shared<Dinner>();
            case SuperAllOutMode::ID:
                return Pointers::shared<SuperAllOutMode>();
            case ForcedRevival::ID:
                return Pointers::shared<ForcedRevival>();
            case OhMyFriend::ID:
                return Pointers::shared<OhMyFriend>();
            case SealedGuardian::ID:
                return Pointers::shared<SealedGuardian>();
            // === Mixed Booster Pack cards ===
            case LonelyChariot::ID:
                return Pointers::shared<LonelyChariot>();
            case Ambush::ID:
                return Pointers::shared<Ambush>();
            case PassionateResearch::ID:
                return Pointers::shared<PassionateResearch>();
            case PresidentsPrivilege::ID:
                return Pointers::shared<PresidentsPrivilege>();
            case Mimic::ID:
                return Pointers::shared<Mimic>();
            case TacticalRetreat::ID:
                return Pointers::shared<TacticalRetreat>();
            case ShieldCounter::ID:
                return Pointers::shared<ShieldCounter>();
            case PiyopiyoProcession::ID:
                return Pointers::shared<PiyopiyoProcession>();
            case SealedMemories::ID:
                return Pointers::shared<SealedMemories>();
            case MixPhenomenon::ID:
                return Pointers::shared<MixPhenomenon>();
            case ScarySolicitation::ID:
                return Pointers::shared<ScarySolicitation>();
            // === Acceleration Pack cards ===
            case CompletionReward::ID:
                return Pointers::shared<CompletionReward>();
            case GentlemansBattle::ID:
                return Pointers::shared<GentlemansBattle>();
            case AccelHyper::ID:
                return Pointers::shared<AccelHyper>();
            case Extension::ID:
                return Pointers::shared<Extension>();
            case QuickRestoration::ID:
                return Pointers::shared<QuickRestoration>();
            case BrutalPrank::ID:
                return Pointers::shared<BrutalPrank>();
            case PresentThief::ID:
                return Pointers::shared<PresentThief>();
            case PlayOfTheGods::ID:
                return Pointers::shared<PlayOfTheGods>();
            case ScrambledEve::ID:
                return Pointers::shared<ScrambledEve>();
            case StarBlastingLight::ID:
                return Pointers::shared<StarBlastingLight>();
            case UnluckyCharm::ID:
                return Pointers::shared<UnluckyCharm>();
            case WindyEnchantment::ID:
                return Pointers::shared<WindyEnchantment>();
            // // === Community Pack 1 cards ===
            // case TreasureThief::ID:
            //     return Pointers::shared<TreasureThief>();
            // case DarkSideOfBusiness::ID:
            //     return Pointers::shared<DarkSideOfBusiness>();
            // case Wanted::ID:
            //     return Pointers::shared<Wanted>();
            // case PartyTime::ID:
            //     return Pointers::shared<PartyTime>();
            // case LostChild::ID:
            //     return Pointers::shared<LostChild>();
            // case PriceOfPower::ID:
            //     return Pointers::shared<PriceOfPower>();
            // /// === Community Pack 2 cards ===
            // case PathBlockers::ID:
            //     return Pointers::shared<PathBlockers>();
            // case DesperateModification::ID:
            //     return Pointers::shared<DesperateModification>();
            // case Poppoformation::ID:
            //     return Pointers::shared<Poppoformation>();
            // case AcceleratingSky::ID:
            //     return Pointers::shared<AcceleratingSky>();
            // case PoppoTheSnatcher::ID:
            //     return Pointers::shared<PoppoTheSnatcher>();
            // case Bloodlust::ID:
            //     return Pointers::shared<Bloodlust>();
            // // === Pudding Pack cards ===
            // case BackdoorTrade::ID:
            //     return Pointers::shared<BackdoorTrade>();
            // case SinkOrSwim::ID:
            //     return Pointers::shared<SinkOrSwim>();
            // case SeriousBattle::ID:
            //     return Pointers::shared<SeriousBattle>();
            // case PortablePudding::ID:
            //     return Pointers::shared<PortablePudding>();
            // case IWannaSeeYou::ID:
            //     return Pointers::shared<IWannaSeeYou>();
            // case Encore::ID:
            //     return Pointers::shared<Encore>();
            // case SweetDestroyer::ID:
            //     return Pointers::shared<SweetDestroyer>();
            // case SereneHush::ID:
            //     return Pointers::shared<SereneHush>();
            // case UnpaidWork::ID:
            //     return Pointers::shared<UnpaidWork>();
            // case IndiscriminateFireSupport::ID:
            //     return Pointers::shared<IndiscriminateFireSupport>();
            // case LuckyCharm::ID:
            //     return Pointers::shared<LuckyCharm>();
            // case MetallicMonocoque::ID:
            //     return Pointers::shared<MetallicMonocoque>();
            // // === Community Pack 3 cards ===
            // case Overtime::ID:
            //     return Pointers::shared<Overtime>();
            // case DeceptiveDisarming::ID:
            //     return Pointers::shared<DeceptiveDisarming>();
            // case BanaNana::ID:
            //     return Pointers::shared<BanaNana>();
            // case PetSnacks::ID:
            //     return Pointers::shared<PetSnacks>();
            // case HomeImprovement::ID:
            //     return Pointers::shared<HomeImprovement>();
            // case LuckySevens::ID:
            //     return Pointers::shared<LuckySevens>();
            // // === Community Pack 4 cards ===
            // case WarpControl::ID:
            //     return Pointers::shared<WarpControl>();
            // case MyWildFriends::ID:
            //     return Pointers::shared<MyWildFriends>();
            // case ContestOfCuteness::ID:
            //     return Pointers::shared<ContestOfCuteness>();
            // case BankOfPoppo::ID:
            //     return Pointers::shared<BankOfPoppo>();
            // case Rebellion::ID:
            //     return Pointers::shared<Rebellion>();
            // case NanakosBit::ID:
            //     return Pointers::shared<NanakosBit>();
            // // === Extracurricular Pack cards ===
            // case FullBurst::ID:
            //     return Pointers::shared<FullBurst>();
            // case ChefsSpecial::ID:
            //     return Pointers::shared<ChefsSpecial>();
            // case GoWithTheFlow::ID:
            //     return Pointers::shared<GoWithTheFlow>();
            // case MousseTheThief::ID:
            //     return Pointers::shared<MousseTheThief>();
            // case ComingBackStronger::ID:
            //     return Pointers::shared<ComingBackStronger>();
            // case ExtremeAlteration::ID:
            //     return Pointers::shared<ExtremeAlteration>();
            // case TheGreatestTroublemakerEver::ID:
            //     return Pointers::shared<TheGreatestTroublemakerEver>();
            // case LookHowLongMyArmsAndLegsAreNow::ID:
            //     return Pointers::shared<LookHowLongMyArmsAndLegsAreNow>();
            // case WereTickedOff::ID:
            //     return Pointers::shared<WereTickedOff>();
            // case ProtectionFee::ID:
            //     return Pointers::shared<ProtectionFee>();
            // case FluffyAndFuzzy::ID:
            //     return Pointers::shared<FluffyAndFuzzy>();
            // case FeelTheRushWithAnEnergyDrink::ID:
            //     return Pointers::shared<FeelTheRushWithAnEnergyDrink>();

            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
