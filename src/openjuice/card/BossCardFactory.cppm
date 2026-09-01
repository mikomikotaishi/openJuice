/**
 * @file BossCardFactory.cppm
 * @module openjuice.card:BossCardFactory
 * @brief Implementation of the BossCardFactory class.
 *
 * This file contains the implementation of the BossCardFactory class, which is used to create BossCard objects.
 */

module;

#include "Macros.hpp"

export module openjuice.card:BossCardFactory;

import :boss;

import stdx;

import openjuice.engine.card;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;

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
    [[nodiscard]]
    static constexpr String secondaryTypeToString(SecondaryType type) noexcept {
        switch (type) {
            case BossCardFactory::SecondaryType::STANDARD:
                return "Standard";
            case BossCardFactory::SecondaryType::HYPER:
                return "Hyper";
        }
        Ops::unreachable();
    }
public:
    BossCardFactory() = delete("BossCardFactory is a utility class and cannot be instantiated.");

    /**
     * @brief Create a BossCard object with the given ID.
     * @param id ID of the BossCard to create
     * @return Shared pointer to the created BossCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static constexpr Optional<SharedPointer<BossCard>> create(u8 id, SecondaryType type = SecondaryType::STANDARD) noexcept {
        switch (type) {
            case SecondaryType::STANDARD:
                switch (id) {
                    case 0:
                        return nullptr;
                    // Big the Haruo's cards
                    // case Doze::ID:
                    //     return Pointers::shared<Doze>();
                    // case GroupUp::ID:
                    //     return Pointers::shared<GroupUp>();
                    // case Peck::ID:
                    //     return Pointers::shared<Peck>();
                    // case Flight::ID:
                    //     return Pointers::shared<Flight>();
                    // case ChickenAttack::ID:
                    //     return Pointers::shared<ChickenAttack>();
                    // case PiyoMarch::ID:
                    //     return Pointers::shared<PiyoMarch>();
                    // case Regeneration::ID:
                    //     return Pointers::shared<Regeneration>();
                    // case Present::ID:
                    //     return Pointers::shared<Present>();
                    // case HeadlessChicken::ID:
                    //     return Pointers::shared<HeadlessChicken>();
                    // case CallOfTheChicken::ID:
                    //     return Pointers::shared<CallOfTheChicken>();
                    // case ChickenRun::ID:
                    //     return Pointers::shared<ChickenRun>();
                    // case HenPecked::ID:
                    //     return Pointers::shared<HenPecked>();
                    // case SecondWing::ID:
                    //     return Pointers::shared<SecondWing>();
                    // case Swarm::ID:
                    //     return Pointers::shared<Swarm>();
                    // case FinalWarning::ID:
                    //     return Pointers::shared<FinalWarning>();
                    // case SavageTalons::ID:
                    //     return Pointers::shared<SavageTalons>();
                    // case BeakOfTheGodbird::ID:
                    //     return Pointers::shared<BeakOfTheGodbird>();
                    // M10 Robot's cards
                    // case Malfunction::ID:
                    //     return Pointers::shared<Malfunction>();
                    // case QuickRepair::ID:
                    //     return Pointers::shared<QuickRepair>();
                    // case BalanceCurrents::ID:
                    //     return Pointers::shared<BalanceCurrents>();
                    // case ImmovableObject::ID:
                    //     return Pointers::shared<ImmovableObject>();
                    // case Turbo::ID:
                    //     return Pointers::shared<Turbo>();
                    // case AssaultField::ID:
                    //     return Pointers::shared<AssaultField>();
                    // case EvasionDown::ID:
                    //     return Pointers::shared<EvasionDown>();
                    // case RoboBeam::ID:
                    //     return Pointers::shared<RoboBeam>();
                    // case DefenseDown::ID:
                    //     return Pointers::shared<DefenseDown>();
                    // case Engage::ID:
                    //     return Pointers::shared<Engage>();
                    // case SelfDestruction::ID:
                    //     return Pointers::shared<SelfDestruction>();
                    // case HealthDown::ID:
                    //     return Pointers::shared<HealthDown>();
                    // case EMP::ID:
                    //     return Pointers::shared<EMP>();
                    // case SolidWitch::ID:
                    //     return Pointers::shared<SolidWitch>();
                    // case AttackDown::ID:
                    //     return Pointers::shared<AttackDown>();
                    // case ImaginaryNumbers::ID:
                    //     return Pointers::shared<ImaginaryNumbers>();
                    // case ScrambledDeltaField::ID:
                    //     return Pointers::shared<ScrambledDeltaField>();
                    // case RecoveryMode::ID:
                    //     return Pointers::shared<RecoveryMode>();
                    // Star Devourer's cards
                    // case Nap::ID:
                    //     return Pointers::shared<Nap>();
                    // case Elusive::ID:
                    //     return Pointers::shared<Elusive>();
                    // case StarMania::ID:
                    //     return Pointers::shared<StarMania>();
                    // case PoppoTax::ID:
                    //     return Pointers::shared<PoppoTax>();
                    // case Ubiquitous::ID:
                    //     return Pointers::shared<Ubiquitous>();
                    // case Snatcher::ID:
                    //     return Pointers::shared<Snatcher>();
                    // case SkyRestaurantPoppoEvent::ID:
                    //     return Pointers::shared<SkyRestaurantPoppoEvent>();
                    // case SkyRestaurantPoppoTrap::ID:
                    //     return Pointers::shared<SkyRestaurantPoppoTrap>();
                    // case HighwayRobbery::ID:
                    //     return Pointers::shared<HighwayRobbery>();
                    // case Greed::ID:
                    //     return Pointers::shared<Greed>();
                    // case WarpPhenomenon::ID:
                    //     return Pointers::shared<WarpPhenomenon>();
                    // case Poppoformation::ID:
                    //     return Pointers::shared<Poppoformation>();
                    // case Temptation::ID:
                    //     return Pointers::shared<Temptation>();
                    // case PoppoGalaxy::ID:
                    //     return Pointers::shared<PoppoGalaxy>();
                    // case DeathAndTaxes::ID:
                    //     return Pointers::shared<DeathAndTaxes>();
                    // case ValueJudgement::ID:
                    //     return Pointers::shared<ValueJudgement>();
                    // case RansomNoteEvent::ID:
                    //     return Pointers::shared<RansomNoteEvent>();
                    // case RansomNoteGift::ID:
                    //     return Pointers::shared<RansomNoteGift>();
                    // case Poppocalypse::ID:
                    //     return Pointers::shared<Poppocalypse>();
                    // Summer Beast's cards
                    // case Rest::ID:
                    //     return Pointers::shared<Rest>();
                    // case Chase::ID:
                    //     return Pointers::shared<Chase>();
                    // case Play::ID:
                    //     return Pointers::shared<Play>();
                    // case TireOut::ID:
                    //     return Pointers::shared<TireOut>();
                    // case PuddingSeeker::ID:
                    //     return Pointers::shared<PuddingSeeker>();
                    // case Birds::ID:
                    //     return Pointers::shared<Birds>();
                    // case SeagullFriend::ID:
                    //     return Pointers::shared<SeagullFriend>();
                    // case DanceOfTheSeagulls::ID:
                    //     return Pointers::shared<DanceOfTheSeagulls>();
                    // case PlayTag::ID:
                    //     return Pointers::shared<PlayTag>();
                    // case HideAndSeek::ID:
                    //     return Pointers::shared<HideAndSeek>();
                    // case SplashWater::ID:
                    //     return Pointers::shared<SplashWater>();
                    // case PsychedUp::ID:
                    //     return Pointers::shared<PsychedUp>();
                    // case PlayWithBirds::ID:
                    //     return Pointers::shared<PlayWithBirds>();
                    // case Exhaustion::ID:
                    //     return Pointers::shared<Exhaustion>();
                    // case SeagullMaster::ID:
                    //     return Pointers::shared<SeagullMaster>();
                    // case WatermelonSplitting::ID:
                    //     return Pointers::shared<WatermelonSplitting>();
                    // case PuddingBreak::ID:
                    //     return Pointers::shared<PuddingBreak>();
                    // case HypeItUp::ID:
                    //     return Pointers::shared<HypeItUp>();
                    // case SandwichThieves::ID:
                    //     return Pointers::shared<SandwichThieves>();
                    // Big the Jonathan's cards
                    // case Snacks::ID:
                    //     return Pointers::shared<Snacks>();
                    // case Screech::ID:
                    //     return Pointers::shared<Screech>();
                    // case Rake::ID:
                    //     return Pointers::shared<Rake>();
                    // case CloudOfSeagulls::ID:
                    //     return Pointers::shared<CloudOfSeagulls>();
                    // case Rush::ID:
                    //     return Pointers::shared<Rush>();
                    // case ChaseAround::ID:
                    //     return Pointers::shared<ChaseAround>();
                    // case Quake::ID:
                    //     return Pointers::shared<Quake>();
                    // case AirRaid::ID:
                    //     return Pointers::shared<AirRaid>();
                    // case DoubleRush::ID:
                    //     return Pointers::shared<DoubleRush>();
                    // case Swipe::ID:
                    //     return Pointers::shared<Swipe>();
                    // case Hunt::ID:
                    //     return Pointers::shared<Hunt>();
                    // case FalseHope::ID:
                    //     return Pointers::shared<FalseHope>();
                    // case Snatch::ID:
                    //     return Pointers::shared<Snatch>();
                    // case AirStrike::ID:
                    //     return Pointers::shared<AirStrike>();
                    // case MegaRush::ID:
                    //     return Pointers::shared<MegaRush>();
                    // case Frantic::ID:
                    //     return Pointers::shared<Frantic>();
                    // case WaveOfDespair::ID:
                    //     return Pointers::shared<WaveOfDespair>();
                    // case AuraOfTerror::ID:
                    //     return Pointers::shared<AuraOfTerror>();
                    // RoPoChi's cards
                    // case IdentityCrisis::ID:
                    //     return Pointers::shared<IdentityCrisis>();
                    // case RoboTax::ID:
                    //     return Pointers::shared<RoboTax>();
                    // case Pluck::ID:
                    //     return Pointers::shared<Pluck>();
                    // case Catcher::ID:
                    //     return Pointers::shared<Catcher>();
                    // case BalanceCurrency::ID:
                    //     return Pointers::shared<BalanceCurrency>();
                    // case PoppoMarch::ID:
                    //     return Pointers::shared<PoppoMarch>();
                    // case PremiumRegeneration::ID:
                    //     return Pointers::shared<PremiumRegeneration>();
                    // case WirelessChicken::ID:
                    //     return Pointers::shared<WirelessChicken>();
                    // case RoPoBarrage::ID:
                    //     return Pointers::shared<RoPoBarrage>();
                    // case DelusionalNumbers::ID:
                    //     return Pointers::shared<DelusionalNumbers>();
                    // case SecondWing::ID:
                    //     return Pointers::shared<SecondWing>();
                    // case PoBomber::ID:
                    //     return Pointers::shared<PoBomber>();
                    // case InvisibleBomb::ID:
                    //     return Pointers::shared<InvisibleBomb>();
                    // case TurboChicken::ID:
                    //     return Pointers::shared<TurboChicken>();
                    // case PoppoUniverse::ID:
                    //     return Pointers::shared<PoppoUniverse>();
                    // case Poppocare::ID:
                    //     return Pointers::shared<Poppocare>();
                    // case RefinedTalons::ID:
                    //     return Pointers::shared<RefinedTalons>();
                    // case BeakOfTheDemiBird::ID:
                    //     return Pointers::shared<BeakOfTheDemiBird>();
                    // case BigPosSpecial::ID:
                    //     return Pointers::shared<BigPosSpecial>();
                    // Swimming Coach's cards
                    // case Float::ID:
                    //     return Pointers::shared<Float>();
                    // case Whirl::ID:
                    //     return Pointers::shared<Whirl>();
                    // case BubbleBath::ID:
                    //     return Pointers::shared<BubbleBath>();
                    // case EntryFee::ID:
                    //     return Pointers::shared<EntryFee>();
                    // case GulpOfWater::ID:
                    //     return Pointers::shared<GulpOfWater>();
                    // case Coaching::ID:
                    //     return Pointers::shared<Coaching>();
                    // case Confiscate::ID:
                    //     return Pointers::shared<Confiscate>();
                    // case Shock::ID:
                    //     return Pointers::shared<Shock>();
                    // case GoFaster::ID:
                    //     return Pointers::shared<GoFaster>();
                    // case Respite::ID:
                    //     return Pointers::shared<Respite>();
                    // case PaceUp::ID:
                    //     return Pointers::shared<PaceUp>();
                    // case Hustle::ID:
                    //     return Pointers::shared<Hustle>();
                    // case Motivate::ID:
                    //     return Pointers::shared<Motivate>();
                    // case TropicalCyclone::ID:
                    //     return Pointers::shared<TropicalCyclone>();
                    // case Butterfly::ID:
                    //     return Pointers::shared<Butterfly>();
                    // case Zap::ID:
                    //     return Pointers::shared<Zap>();
                    // case Encourage::ID:
                    //     return Pointers::shared<Encourage>();
                    // case MovingTheGoalpost::ID:
                    //     return Pointers::shared<MovingTheGoalpost>();
                    default:
                        return nullopt;
                }
            case SecondaryType::HYPER:
                switch (id) {
                    case 0:
                        return nullptr;
                    // case Roost::ID:
                    //     return Pointers::shared<Roost>();
                    // case HyperRoost::ID:
                    //     return Pointers::shared<HyperRoost>();
                    // case Protect::ID:
                    //     return Pointers::shared<Protect>();
                    // case PerfectReflectiveShell::ID:
                    //     return Pointers::shared<PerfectReflectiveShell>();
                    // case FromTheAbyss::ID:
                    //     return Pointers::shared<FromTheAbyss>();
                    // case HypeMode::ID:
                    //     return Pointers::shared<HypeMode>();
                    // case Rampage::ID:
                    //     return Pointers::shared<Rampage>();
                    // case HyperRampage::ID:
                    //     return Pointers::shared<HyperRampage>();
                    // case Launch::ID:
                    //     return Pointers::shared<Launch>();
                    // case Dive::ID:
                    //     return Pointers::shared<Dive>();
                    // case RoostBoost::ID:
                    //     return Pointers::shared<RoostBoost>();
                    // case PoTect::ID:
                    //     return Pointers::shared<PoTect>();
                    // case Goalpost::ID:
                    //     return Pointers::shared<Goalpost>();
                    // case BalloonJerk::ID:
                    //     return Pointers::shared<BalloonJerk>();
                    // case SwimmingRinger::ID:
                    //     return Pointers::shared<SwimmingRinger>();
                    // case HomeSweeper::ID:
                    //     return Pointers::shared<HomeSweeper>();
                    default:
                        return nullopt;
                }
        }
        Ops::unreachable();
    }
};

END_MODULE_NAMESPACE();

using openjuice::card::BossCardFactory;

namespace stdx::fmt {
    template <>
    struct Formatter<BossCardFactory::SecondaryType> {
        static constexpr const char* parse(FormatParseContext& ctx) noexcept {
            return ctx.begin();
        }

        static FormatContext::iterator format(BossCardFactory::SecondaryType type, FormatContext& ctx) {
            StringView name;
            switch (type) {
                case BossCardFactory::SecondaryType::STANDARD:
                    name = "Standard";
                    break;
                case BossCardFactory::SecondaryType::HYPER:
                    name = "Hyper";
                    break;
            }
            return format_to(ctx.out(), "{}", name);
        }
    };
}

SPECIALIZE_FORMATTER(BossCardFactory::SecondaryType);
