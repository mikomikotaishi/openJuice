/**
 * @file BossCardFactory.cppm
 * @module openjuice.card:BossCardFactory
 * @brief Implementation of the BossCardFactory class.
 *
 * This file contains the implementation of the BossCardFactory class, which is used to create BossCard objects.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.card:BossCardFactory;

import stdx;

import openjuice.engine.card;
import openjuice.engine.managers;
import openjuice.card.boss;

using stdx::fmt::FormatContext;
using stdx::fmt::FormatParseContext;
using stdx::fmt::Formatter;
using stdx::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::card::spawn::BossCard;

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
public:
    /** 
     * @enum SecondaryType
     * @brief The secondary type, used to specify to the factory what the ID is in relation to.
     */
    enum class SecondaryType: u8 {
        STANDARD, ///< A BossCard of standard variety
        HYPER, ///< A BossCard of hyper variety
    };
private:
    UTILITY_CLASS(BossCardFactory);

    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("BossCardFactory"); ///< The logger instance.

    [[nodiscard]]
    static constexpr String secondaryTypeToString(SecondaryType type) noexcept {
        switch (type) {
            case BossCardFactory::SecondaryType::STANDARD:
                return "Standard";
            case BossCardFactory::SecondaryType::HYPER:
                return "Hyper";
            default:
                stdx::sys::unreachable();
        }
    }
public:
    /**
     * @brief Create a BossCard object with the given ID.
     *
     * @param id ID of the BossCard to create
     * @return Shared pointer to the created BossCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<BossCard>> create(u8 id, SecondaryType type = SecondaryType::STANDARD) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating BossCard of ID: {}, secondary type: {}", id, secondaryTypeToString(type));
        #endif

        switch (type) {
            case SecondaryType::STANDARD:
                switch (id) {
                    case 0:
                        return nullptr;
                    // Big the Haruo's cards
                    // case Doze::ID:
                    //     return stdx::mem::make_shared<Doze>();
                    // case GroupUp::ID:
                    //     return stdx::mem::make_shared<GroupUp>();
                    // case Peck::ID:
                    //     return stdx::mem::make_shared<Peck>();
                    // case Flight::ID:
                    //     return stdx::mem::make_shared<Flight>();
                    // case ChickenAttack::ID:
                    //     return stdx::mem::make_shared<ChickenAttack>();
                    // case PiyoMarch::ID:
                    //     return stdx::mem::make_shared<PiyoMarch>();
                    // case Regeneration::ID:
                    //     return stdx::mem::make_shared<Regeneration>();
                    // case Present::ID:
                    //     return stdx::mem::make_shared<Present>();
                    // case HeadlessChicken::ID:
                    //     return stdx::mem::make_shared<HeadlessChicken>();
                    // case CallOfTheChicken::ID:
                    //     return stdx::mem::make_shared<CallOfTheChicken>();
                    // case ChickenRun::ID:
                    //     return stdx::mem::make_shared<ChickenRun>();
                    // case HenPecked::ID:
                    //     return stdx::mem::make_shared<HenPecked>();
                    // case SecondWing::ID:
                    //     return stdx::mem::make_shared<SecondWing>();
                    // case Swarm::ID:
                    //     return stdx::mem::make_shared<Swarm>();
                    // case FinalWarning::ID:
                    //     return stdx::mem::make_shared<FinalWarning>();
                    // case SavageTalons::ID:
                    //     return stdx::mem::make_shared<SavageTalons>();
                    // case BeakOfTheGodbird::ID:
                    //     return stdx::mem::make_shared<BeakOfTheGodbird>();
                    // M10 Robot's cards
                    // case Malfunction::ID:
                    //     return stdx::mem::make_shared<Malfunction>();
                    // case QuickRepair::ID:
                    //     return stdx::mem::make_shared<QuickRepair>();
                    // case BalanceCurrents::ID:
                    //     return stdx::mem::make_shared<BalanceCurrents>();
                    // case ImmovableObject::ID:
                    //     return stdx::mem::make_shared<ImmovableObject>();
                    // case Turbo::ID:
                    //     return stdx::mem::make_shared<Turbo>();
                    // case AssaultField::ID:
                    //     return stdx::mem::make_shared<AssaultField>();
                    // case EvasionDown::ID:
                    //     return stdx::mem::make_shared<EvasionDown>();
                    // case RoboBeam::ID:
                    //     return stdx::mem::make_shared<RoboBeam>();
                    // case DefenseDown::ID:
                    //     return stdx::mem::make_shared<DefenseDown>();
                    // case Engage::ID:
                    //     return stdx::mem::make_shared<Engage>();
                    // case SelfDestruction::ID:
                    //     return stdx::mem::make_shared<SelfDestruction>();
                    // case HealthDown::ID:
                    //     return stdx::mem::make_shared<HealthDown>();
                    // case EMP::ID:
                    //     return stdx::mem::make_shared<EMP>();
                    // case SolidWitch::ID:
                    //     return stdx::mem::make_shared<SolidWitch>();
                    // case AttackDown::ID:
                    //     return stdx::mem::make_shared<AttackDown>();
                    // case ImaginaryNumbers::ID:
                    //     return stdx::mem::make_shared<ImaginaryNumbers>();
                    // case ScrambledDeltaField::ID:
                    //     return stdx::mem::make_shared<ScrambledDeltaField>();
                    // case RecoveryMode::ID:
                    //     return stdx::mem::make_shared<RecoveryMode>();
                    // Star Devourer's cards
                    // case Nap::ID:
                    //     return stdx::mem::make_shared<Nap>();
                    // case Elusive::ID:
                    //     return stdx::mem::make_shared<Elusive>();
                    // case StarMania::ID:
                    //     return stdx::mem::make_shared<StarMania>();
                    // case PoppoTax::ID:
                    //     return stdx::mem::make_shared<PoppoTax>();
                    // case Ubiquitous::ID:
                    //     return stdx::mem::make_shared<Ubiquitous>();
                    // case Snatcher::ID:
                    //     return stdx::mem::make_shared<Snatcher>();
                    // case SkyRestaurantPoppoEvent::ID:
                    //     return stdx::mem::make_shared<SkyRestaurantPoppoEvent>();
                    // case SkyRestaurantPoppoTrap::ID:
                    //     return stdx::mem::make_shared<SkyRestaurantPoppoTrap>();
                    // case HighwayRobbery::ID:
                    //     return stdx::mem::make_shared<HighwayRobbery>();
                    // case Greed::ID:
                    //     return stdx::mem::make_shared<Greed>();
                    // case WarpPhenomenon::ID:
                    //     return stdx::mem::make_shared<WarpPhenomenon>();
                    // case Poppoformation::ID:
                    //     return stdx::mem::make_shared<Poppoformation>();
                    // case Temptation::ID:
                    //     return stdx::mem::make_shared<Temptation>();
                    // case PoppoGalaxy::ID:
                    //     return stdx::mem::make_shared<PoppoGalaxy>();
                    // case DeathAndTaxes::ID:
                    //     return stdx::mem::make_shared<DeathAndTaxes>();
                    // case ValueJudgement::ID:
                    //     return stdx::mem::make_shared<ValueJudgement>();
                    // case RansomNoteEvent::ID:
                    //     return stdx::mem::make_shared<RansomNoteEvent>();
                    // case RansomNoteGift::ID:
                    //     return stdx::mem::make_shared<RansomNoteGift>();
                    // case Poppocalypse::ID:
                    //     return stdx::mem::make_shared<Poppocalypse>();
                    // Summer Beast's cards
                    // case Rest::ID:
                    //     return stdx::mem::make_shared<Rest>();
                    // case Chase::ID:
                    //     return stdx::mem::make_shared<Chase>();
                    // case Play::ID:
                    //     return stdx::mem::make_shared<Play>();
                    // case TireOut::ID:
                    //     return stdx::mem::make_shared<TireOut>();
                    // case PuddingSeeker::ID:
                    //     return stdx::mem::make_shared<PuddingSeeker>();
                    // case Birds::ID:
                    //     return stdx::mem::make_shared<Birds>();
                    // case SeagullFriend::ID:
                    //     return stdx::mem::make_shared<SeagullFriend>();
                    // case DanceOfTheSeagulls::ID:
                    //     return stdx::mem::make_shared<DanceOfTheSeagulls>();
                    // case PlayTag::ID:
                    //     return stdx::mem::make_shared<PlayTag>();
                    // case HideAndSeek::ID:
                    //     return stdx::mem::make_shared<HideAndSeek>();
                    // case SplashWater::ID:
                    //     return stdx::mem::make_shared<SplashWater>();
                    // case PsychedUp::ID:
                    //     return stdx::mem::make_shared<PsychedUp>();
                    // case PlayWithBirds::ID:
                    //     return stdx::mem::make_shared<PlayWithBirds>();
                    // case Exhaustion::ID:
                    //     return stdx::mem::make_shared<Exhaustion>();
                    // case SeagullMaster::ID:
                    //     return stdx::mem::make_shared<SeagullMaster>();
                    // case WatermelonSplitting::ID:
                    //     return stdx::mem::make_shared<WatermelonSplitting>();
                    // case PuddingBreak::ID:
                    //     return stdx::mem::make_shared<PuddingBreak>();
                    // case HypeItUp::ID:
                    //     return stdx::mem::make_shared<HypeItUp>();
                    // case SandwichThieves::ID:
                    //     return stdx::mem::make_shared<SandwichThieves>();
                    // Big the Jonathan's cards
                    // case Snacks::ID:
                    //     return stdx::mem::make_shared<Snacks>();
                    // case Screech::ID:
                    //     return stdx::mem::make_shared<Screech>();
                    // case Rake::ID:
                    //     return stdx::mem::make_shared<Rake>();
                    // case CloudOfSeagulls::ID:
                    //     return stdx::mem::make_shared<CloudOfSeagulls>();
                    // case Rush::ID:
                    //     return stdx::mem::make_shared<Rush>();
                    // case ChaseAround::ID:
                    //     return stdx::mem::make_shared<ChaseAround>();
                    // case Quake::ID:
                    //     return stdx::mem::make_shared<Quake>();
                    // case AirRaid::ID:
                    //     return stdx::mem::make_shared<AirRaid>();
                    // case DoubleRush::ID:
                    //     return stdx::mem::make_shared<DoubleRush>();
                    // case Swipe::ID:
                    //     return stdx::mem::make_shared<Swipe>();
                    // case Hunt::ID:
                    //     return stdx::mem::make_shared<Hunt>();
                    // case FalseHope::ID:
                    //     return stdx::mem::make_shared<FalseHope>();
                    // case Snatch::ID:
                    //     return stdx::mem::make_shared<Snatch>();
                    // case AirStrike::ID:
                    //     return stdx::mem::make_shared<AirStrike>();
                    // case MegaRush::ID:
                    //     return stdx::mem::make_shared<MegaRush>();
                    // case Frantic::ID:
                    //     return stdx::mem::make_shared<Frantic>();
                    // case WaveOfDespair::ID:
                    //     return stdx::mem::make_shared<WaveOfDespair>();
                    // case AuraOfTerror::ID:
                    //     return stdx::mem::make_shared<AuraOfTerror>();
                    // RoPoChi's cards
                    // case IdentityCrisis::ID:
                    //     return stdx::mem::make_shared<IdentityCrisis>();
                    // case RoboTax::ID:
                    //     return stdx::mem::make_shared<RoboTax>();
                    // case Pluck::ID:
                    //     return stdx::mem::make_shared<Pluck>();
                    // case Catcher::ID:
                    //     return stdx::mem::make_shared<Catcher>();
                    // case BalanceCurrency::ID:
                    //     return stdx::mem::make_shared<BalanceCurrency>();
                    // case PoppoMarch::ID:
                    //     return stdx::mem::make_shared<PoppoMarch>();
                    // case PremiumRegeneration::ID:
                    //     return stdx::mem::make_shared<PremiumRegeneration>();
                    // case WirelessChicken::ID:
                    //     return stdx::mem::make_shared<WirelessChicken>();
                    // case RoPoBarrage::ID:
                    //     return stdx::mem::make_shared<RoPoBarrage>();
                    // case DelusionalNumbers::ID:
                    //     return stdx::mem::make_shared<DelusionalNumbers>();
                    // case SecondWing::ID:
                    //     return stdx::mem::make_shared<SecondWing>();
                    // case PoBomber::ID:
                    //     return stdx::mem::make_shared<PoBomber>();
                    // case InvisibleBomb::ID:
                    //     return stdx::mem::make_shared<InvisibleBomb>();
                    // case TurboChicken::ID:
                    //     return stdx::mem::make_shared<TurboChicken>();
                    // case PoppoUniverse::ID:
                    //     return stdx::mem::make_shared<PoppoUniverse>();
                    // case Poppocare::ID:
                    //     return stdx::mem::make_shared<Poppocare>();
                    // case RefinedTalons::ID:
                    //     return stdx::mem::make_shared<RefinedTalons>();
                    // case BeakOfTheDemiBird::ID:
                    //     return stdx::mem::make_shared<BeakOfTheDemiBird>();
                    // case BigPosSpecial::ID:
                    //     return stdx::mem::make_shared<BigPosSpecial>();
                    // Swimming Coach's cards
                    // case Float::ID:
                    //     return stdx::mem::make_shared<Float>();
                    // case Whirl::ID:
                    //     return stdx::mem::make_shared<Whirl>();
                    // case BubbleBath::ID:
                    //     return stdx::mem::make_shared<BubbleBath>();
                    // case EntryFee::ID:
                    //     return stdx::mem::make_shared<EntryFee>();
                    // case GulpOfWater::ID:
                    //     return stdx::mem::make_shared<GulpOfWater>();
                    // case Coaching::ID:
                    //     return stdx::mem::make_shared<Coaching>();
                    // case Confiscate::ID:
                    //     return stdx::mem::make_shared<Confiscate>();
                    // case Shock::ID:
                    //     return stdx::mem::make_shared<Shock>();
                    // case GoFaster::ID:
                    //     return stdx::mem::make_shared<GoFaster>();
                    // case Respite::ID:
                    //     return stdx::mem::make_shared<Respite>();
                    // case PaceUp::ID:
                    //     return stdx::mem::make_shared<PaceUp>();
                    // case Hustle::ID:
                    //     return stdx::mem::make_shared<Hustle>();
                    // case Motivate::ID:
                    //     return stdx::mem::make_shared<Motivate>();
                    // case TropicalCyclone::ID:
                    //     return stdx::mem::make_shared<TropicalCyclone>();
                    // case Butterfly::ID:
                    //     return stdx::mem::make_shared<Butterfly>();
                    // case Zap::ID:
                    //     return stdx::mem::make_shared<Zap>();
                    // case Encourage::ID:
                    //     return stdx::mem::make_shared<Encourage>();
                    // case MovingTheGoalpost::ID:
                    //     return stdx::mem::make_shared<MovingTheGoalpost>();
                    default:
                        return nullopt;
                }
            case SecondaryType::HYPER:
                switch (id) {
                    case 0:
                        return nullptr;
                    // case Roost::ID:
                    //     return stdx::mem::make_shared<Roost>();
                    // case HyperRoost::ID:
                    //     return stdx::mem::make_shared<HyperRoost>();
                    // case Protect::ID:
                    //     return stdx::mem::make_shared<Protect>();
                    // case PerfectReflectiveShell::ID:
                    //     return stdx::mem::make_shared<PerfectReflectiveShell>();
                    // case FromTheAbyss::ID:
                    //     return stdx::mem::make_shared<FromTheAbyss>();
                    // case HypeMode::ID:
                    //     return stdx::mem::make_shared<HypeMode>();
                    // case Rampage::ID:
                    //     return stdx::mem::make_shared<Rampage>();
                    // case HyperRampage::ID:
                    //     return stdx::mem::make_shared<HyperRampage>();
                    // case Launch::ID:
                    //     return stdx::mem::make_shared<Launch>();
                    // case Dive::ID:
                    //     return stdx::mem::make_shared<Dive>();
                    // case RoostBoost::ID:
                    //     return stdx::mem::make_shared<RoostBoost>();
                    // case PoTect::ID:
                    //     return stdx::mem::make_shared<PoTect>();
                    // case Goalpost::ID:
                    //     return stdx::mem::make_shared<Goalpost>();
                    // case BalloonJerk::ID:
                    //     return stdx::mem::make_shared<BalloonJerk>();
                    // case SwimmingRinger::ID:
                    //     return stdx::mem::make_shared<SwimmingRinger>();
                    // case HomeSweeper::ID:
                    //     return stdx::mem::make_shared<HomeSweeper>();
                    default:
                        return nullopt;
                }
            default:
                stdx::sys::unreachable();
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
                stdx::sys::unreachable();
        }
        return stdx::fmt::format_to(ctx.out(), "{}", name);
    }
};

SPECIALISE_FORMATTER(BossCardFactory::SecondaryType);
