/**
 * @file HyperCardFactory.cppm
 * @module openjuice.card:HyperCardFactory
 * @brief Implementation of the HyperCardFactory class.
 *
 * This file contains the implementation of the HyperCardFactory class, which is used to create HyperCard objects.
 */

module;

#include "Macros.hpp"

export module openjuice.card:HyperCardFactory;

import :hyper;

import stdx;

import openjuice.engine.card;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;

using openjuice::engine::card::spawn::HyperCard;

using namespace openjuice::card::hyper;

BEGIN_MODULE_NAMESPACE(openjuice::card);

/**
 * @class HyperCardFactory
 * @brief Factory class for creating HyperCard objects.
 *
 * The HyperCardFactory class is a singleton factory class that creates HyperCard objects based on the given ID.
 */
export class HyperCardFactory final {
public:
    HyperCardFactory() = delete("HyperCardFactory is a utility class and cannot be instantiated.");

    /**
     * @brief Create a HyperCard object with the given ID.
     * @param id ID of the HyperCard to create
     * @return Shared pointer to the created HyperCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static constexpr Optional<SharedPointer<HyperCard>> create(u16 id) noexcept {
        switch (id) {
            case 0:
                return nullptr;
            // === Main character hyper cards ===
            case ProtagonistsPrivilege::ID:
                return Pointers::shared<ProtagonistsPrivilege>();
            case X16BigRocket::ID:
                return Pointers::shared<X16BigRocket>();
            case HyperMode::ID:
                return Pointers::shared<HyperMode>();
            case Accelerator::ID:
                return Pointers::shared<Accelerator>();
            // === Unlockable character hyper cards ===
            case PresentForYou::ID:
                return Pointers::shared<PresentForYou>();
            case AirStrike::ID:
                return Pointers::shared<AirStrike>();
            case BindingChains::ID:
                return Pointers::shared<BindingChains>();
            case Ubiquitous::ID:
                return Pointers::shared<Ubiquitous>();
            case MagicalInferno::ID:
                return Pointers::shared<MagicalInferno>();
            case ChristmasInferno::ID:
                return Pointers::shared<ChristmasInferno>();
            case BlueCrowTheSecond::ID:
                return Pointers::shared<BlueCrowTheSecond>();
            case ExtraordinarySpecs::ID:
                return Pointers::shared<ExtraordinarySpecs>();
            case MagicalMassacre::ID:
                return Pointers::shared<MagicalMassacre>();
            case Gamble::ID:
                return Pointers::shared<Gamble>();
            // === Store-unlocked character hyper cards ===
            // case GoldenEgg::ID:
            //     return Pointers::shared<GoldenEgg>();
            // case ReflectiveShell::ID:
            //     return Pointers::shared<ReflectiveShell>();
            // case JonathanRush::ID:
            //     return Pointers::shared<JonathanRush>();
            // case BannedForLife::ID:
            //     return Pointers::shared<BannedForLife>();
            // case TurboCharged::ID:
            //     return Pointers::shared<TurboCharged>();
            // case ImmovableObject::ID:
            //     return Pointers::shared<ImmovableObject>();
            // === DLC-unlocked character hyper cards ===
            // case BeyondHell::ID:
            //     return Pointers::shared<BeyondHell>();
            // case DeployBits::ID:
            //     return Pointers::shared<DeployBits>();
            // case SweetGuardian::ID:
            //     return Pointers::shared<SweetGuardian>();
            // case BigBangBell::ID:
            //     return Pointers::shared<BigBangBell>();
            // case CastOff::ID:
            //     return Pointers::shared<CastOff>();
            // case PlushieMaster::ID:
            //     return Pointers::shared<PlushieMaster>(); // Sets DanceLongEaredBeasts trap when activated
            // case Blazing::ID:
            //     return Pointers::shared<Blazing>();
            // case SelfDestruct::ID:
            //     return Pointers::shared<SelfDestruct>();
            // case CrystalBarrier::ID:
            //     return Pointers::shared<CrystalBarrier>();
            // case SubspaceTunnel::ID:
            //     return Pointers::shared<SubspaceTunnel>();
            // case DeltaField::ID:
            //     return Pointers::shared<DeltaField>();
            // case WhimsicalWindmill::ID:
            //     return Pointers::shared<WhimsicalWindmill>();
            // case AwakeningOfTalent::ID:
            //     return Pointers::shared<AwakeningOfTalent>();
            // case StarBlastingFuse::ID:
            //     return Pointers::shared<StarBlastingFuse>(); // Sets InvisibleBomb trap when activated
            // case MeltingMemories::ID:
            //     return Pointers::shared<MeltingMemories>();
            // case SantasJob::ID:
            //     return Pointers::shared<SantasJob>();
            // case AnotherUltimateWeapon::ID:
            //     return Pointers::shared<AnotherUltimateWeapon>();
            // case EvilSpyWorkPreparation::ID:
            //     return Pointers::shared<EvilSpyWorkPreparation>(); // Sets EvilSpyWorkExecution trap when activated
            // case WarudaMachineBlastOff::ID:
            //     return Pointers::shared<WarudaMachineBlastOff>();
            // case FinalSurgery::ID:
            //     return Pointers::shared<FinalSurgery>();
            // case 41:
            // case Overseer::ID:
            //     return Pointers::shared<Overseer>();
            // case WitchsHairLock::ID:
            //     return Pointers::shared<WitchsHairLock>();
            // case SolidWitch::ID:
            //     return Pointers::shared<SolidWitch>();
            // case EvilMastermind::ID:
            //     return Pointers::shared<EvilMastermind>();
            // case MiracleRedBeanIceCream::ID:
            //     return Pointers::shared<MiracleRedBeanIceCream>();
            // case MagicalRevenge::ID:
            //     return Pointers::shared<MagicalRevenge>();
            // case RevivalOfStars::ID:
            //     return Pointers::shared<RevivalOfStars>();
            // case StealthOn::ID:
            //     return Pointers::shared<StealthOn>();
            // case DoPiratesFlyInTheSky::ID:
            //     return Pointers::shared<DoPiratesFlyInTheSky>(); // Sets FlyingPirate trap when activated
            // case WhiteChristmasher::ID:
            //     return Pointers::shared<WhiteChristmasher>(); // Converts to TrueWhiteChristmasher when carrying RedAndBlue
            // case CookingTime::ID:
            //     return Pointers::shared<CookingTime>();
            // case MiracleWalker::ID:
            //     return Pointers::shared<MiracleWalker>();
            // case BranchExplosionStrategy::ID:
            //     return Pointers::shared<BranchExplosionStrategy>(); // Converts all cards to RbitHobbyShop
            // case ExtendedPhotonRifle::ID:
            //     return Pointers::shared<ExtendedPhotonRifle>();
            // case LeapThroughSpaceMarking::ID:
            //     return Pointers::shared<LeapThroughSpaceMarking>(); // Converts to LeapThroughSpace when activated
            // case SpecialStage::ID:
            //     return Pointers::shared<SpecialStage>();
            // case YuukiHand::ID:
            //     return Pointers::shared<YuukiHand>(); // Alternates between AngelHand (even chapters) and DevilHand (odd chapters)
            // case Rival::ID:
            //     return Pointers::shared<Rival>();
            // case ObserverOfEternity::ID:
            //     return Pointers::shared<ObserverOfEternity>();
            // case ReproductionOfRecords::ID:
            //     return Pointers::shared<ReproductionOfRecords>();
            // case ElliesMiracle::ID:
            //     return Pointers::shared<ElliesMiracle>();
            // case LulusLuckyEgg::ID:
            //     return Pointers::shared<LulusLuckyEgg>();
            // case RocketCannon::ID:
            //     return Pointers::shared<RocketCannon>(); // Converts to BigRocketCannon if alternate effect is used
            // case FullSpeedAlicianrone::ID:
            //     return Pointers::shared<FullSpeedAlicianrone>();
            // case BeastWitch::ID:
            //     return Pointers::shared<BeastWitch>();
            // case IntelligenceOfficer::ID:
            //     return Pointers::shared<IntelligenceOfficer>();
            // case RagingMadness::ID:
            //     return Pointers::shared<RagingMadness>();
            // case SaintEyes::ID:
            //     return Pointers::shared<SaintEyes>();
            // case ChefICouldUseSomeHelp::ID:
            //     return Pointers::shared<ChefICouldUseSomeHelp>(); // Converts to ManagerICouldUseSomeHelp when having 4 or more store manager counters and at least level 4
            // case SafeJourney::ID:
            //     return Pointers::shared<SafeJourney>();
            // case GuidanceOfTheWeathercock::ID:
            //     return Pointers::shared<GuidanceOfTheWeathercock>();
            // case Upshift::ID:
            //     return Pointers::shared<Upshift>();
            // case ZealousSalesman::ID:
            //     return Pointers::shared<ZealousSalesman>();
            // case DanceInTheMoonlitNight::ID:
            //     return Pointers::shared<DanceInTheMoonlitNight>();
            // case NewNobility::ID:
            //     return Pointers::shared<NewNobility>(); // Converts to Affluence if held by FernetNoble
            // case TwilightColoredDream::ID:
            //     return Pointers::shared<TwilightColoredDream>();
            // case LittleMagnum::ID:
            //     return Pointers::shared<LittleMagnum>();
            // case IdealWorld::ID:
            //     return Pointers::shared<IdealWorld>();
            // case StarCollector::ID:
            //     return Pointers::shared<StarCollector>();
            // case TorrentOfMagic::ID:
            //     return Pointers::shared<TorrentOfMagic>();
            // case GoodestBoy::ID:
            //     return Pointers::shared<GoodestBoy>();
            // case SweetParadise::ID:
            //     return Pointers::shared<SweetParadise>(); // Sets SweetIndulgence trap when activated
            // case SweetMakersMagic::ID:
            //     return Pointers::shared<SweetMakersMagic>();
            // case OperationAMountainOfSweets::ID:
            //     return Pointers::shared<OperationAMountainOfSweets>();
            // case ThreatsToMySlumber::ID:
            //     return Pointers::shared<ThreatsToMySlumber>(); // Converts to WhenMySlumberBreaks when activated
            // case MakeBelievePrisonBreak::ID:
            //     return Pointers::shared<MakeBelievePrisonBreak>();
            // case MotherPower::ID:
            //     return Pointers::shared<MotherPower>();
            // case LuluIsAnUnluckyDragon::ID:
            //     return Pointers::shared<LuluIsAnUnluckyDragon>();
            // case ElliesHyperMiracle::ID:
            //     return Pointers::shared<ElliesHyperMiracle>();
            // case ExProtagonistsMomentOfGlory::ID:
            //     return Pointers::shared<ExProtagonistsMomentOfGlory>();
            // case AllGunsAtTheReady::ID:
            //     return Pointers::shared<AllGunsAtTheReady>();
            // case HeartOfResistance::ID:
            //     return Pointers::shared<HeartOfResistance>();
            // case SuperYouthTime::ID:
            //     return Pointers::shared<SuperYouthTime>();
            // case IllGetALittleIntoIt::ID:
            //     return Pointers::shared<IllGetALittleIntoIt>();
            // case HypeBringer::ID:
            //     return Pointers::shared<HypeBringer>();
            // case IntellectualSoundingBluff::ID:
            //     return Pointers::shared<IntellectualSoundingBluff>();
            // === 3.28.1 onwards ===
            // case PreciseDiceRolls::ID:
            //     return Pointers::shared<PreciseDiceRolls>();
            // case BecauseImATeacher::ID:
            //     return Pointers::shared<BecauseImATeacher>();
            // case HardworkingGyaruStudentCouncilPresident::ID:
            //     return Pointers::shared<HardworkingGyaruStudentCouncilPresident>();
            // === Hyper cards part of another hyper card ===
            // case DanceLongHairedBeasts::ID:
            //     return Pointers::shared<DanceLongHairedBeasts>();
            // case InvisibleBomb::ID:
            //     return Pointers::shared<InvisibleBomb>();
            // case EvilSpyWorkExecution::ID:
            //     return Pointers::shared<EvilSpyWorkExecution>();
            // case FlyingPirate::ID:
            //     return Pointers::shared<FlyingPirate>();
            // case TrueWhiteChristmasher::ID:
            //     return Pointers::shared<TrueWhiteChristmasher>();
            // case RbitHobbyShop::ID:
            //     return Pointers::shared<RbitHobbyShop>();
            // case LeapThroughSpace::ID:
            //     return Pointers::shared<LeapThroughSpace>();
            // case AngelHand::ID:
            //     return Pointers::shared<AngelHand>();
            // case DevilHand::ID:
            //     return Pointers::shared<DevilHand>();
            // case BigRocketCannon::ID:
            //     return Pointers::shared<BigRocketCannon>();
            // case ManagerICouldUseSomeHelp::ID:
            //     return Pointers::shared<ManagerICouldUseSomeHelp>();
            // case Affluence::ID:
            //     return Pointers::shared<Affluence>();
            // case SweetIndulgence::ID:
            //     return Pointers::shared<SweetIndulgence>();
            // case WhenMySlumberBreaks::ID:
            //     return Pointers::shared<WhenMySlumberBreaks>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
