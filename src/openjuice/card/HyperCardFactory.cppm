/**
 * @file HyperCardFactory.cppm
 * @module openjuice.card:HyperCardFactory
 * @brief Implementation of the HyperCardFactory class.
 *
 * This file contains the implementation of the HyperCardFactory class, which is used to create HyperCard objects.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.card:HyperCardFactory;

import stdx;

import openjuice.engine.card;
import openjuice.engine.managers;
import openjuice.card.hyper;

using stdx::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using openjuice::engine::card::spawntypes::HyperCard;

using namespace openjuice::card::hyper;

BEGIN_MODULE_NAMESPACE(openjuice::card);

/**
 * @class HyperCardFactory
 * @brief Factory class for creating HyperCard objects.
 *
 * The HyperCardFactory class is a singleton factory class that creates HyperCard objects based on the given ID.
 */
export class HyperCardFactory final {
private:
    UTILITY_CLASS(HyperCardFactory);

    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("HyperCardFactory"); ///< The logger instance.
public:
    /**
     * @brief Create a HyperCard object with the given ID.
     *
     * @param id ID of the HyperCard to create
     * @return Shared pointer to the created HyperCard object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<HyperCard>> create(u16 id) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating HyperCard of ID: {}", id);
        #endif

        switch (id) {
            case 0:
                return nullptr;
            // === Main character hyper cards ===
            case ProtagonistsPrivilege::ID:
                return stdx::mem::make_shared<ProtagonistsPrivilege>();
            case X16BigRocket::ID:
                return stdx::mem::make_shared<X16BigRocket>();
            case HyperMode::ID:
                return stdx::mem::make_shared<HyperMode>();
            case Accelerator::ID:
                return stdx::mem::make_shared<Accelerator>();
            // === Unlockable character hyper cards ===
            case PresentForYou::ID:
                return stdx::mem::make_shared<PresentForYou>();
            case AirStrike::ID:
                return stdx::mem::make_shared<AirStrike>();
            case BindingChains::ID:
                return stdx::mem::make_shared<BindingChains>();
            case Ubiquitous::ID:
                return stdx::mem::make_shared<Ubiquitous>();
            case MagicalInferno::ID:
                return stdx::mem::make_shared<MagicalInferno>();
            case ChristmasInferno::ID:
                return stdx::mem::make_shared<ChristmasInferno>();
            case BlueCrowTheSecond::ID:
                return stdx::mem::make_shared<BlueCrowTheSecond>();
            case ExtraordinarySpecs::ID:
                return stdx::mem::make_shared<ExtraordinarySpecs>();
            case MagicalMassacre::ID:
                return stdx::mem::make_shared<MagicalMassacre>();
            case Gamble::ID:
                return stdx::mem::make_shared<Gamble>();
            // === Store-unlocked character hyper cards ===
            // case GoldenEgg::ID:
            //     return stdx::mem::make_shared<GoldenEgg>();
            // case ReflectiveShell::ID:
            //     return stdx::mem::make_shared<ReflectiveShell>();
            // case JonathanRush::ID:
            //     return stdx::mem::make_shared<JonathanRush>();
            // case BannedForLife::ID:
            //     return stdx::mem::make_shared<BannedForLife>();
            // case TurboCharged::ID:
            //     return stdx::mem::make_shared<TurboCharged>();
            // case ImmovableObject::ID:
            //     return stdx::mem::make_shared<ImmovableObject>();
            // === DLC-unlocked character hyper cards ===
            // case BeyondHell::ID:
            //     return stdx::mem::make_shared<BeyondHell>();
            // case DeployBits::ID:
            //     return stdx::mem::make_shared<DeployBits>();
            // case SweetGuardian::ID:
            //     return stdx::mem::make_shared<SweetGuardian>();
            // case BigBangBell::ID:
            //     return stdx::mem::make_shared<BigBangBell>();
            // case CastOff::ID:
            //     return stdx::mem::make_shared<CastOff>();
            // case PlushieMaster::ID:
            //     return stdx::mem::make_shared<PlushieMaster>(); // Sets DanceLongEaredBeasts trap when activated
            // case Blazing::ID:
            //     return stdx::mem::make_shared<Blazing>();
            // case SelfDestruct::ID:
            //     return stdx::mem::make_shared<SelfDestruct>();
            // case CrystalBarrier::ID:
            //     return stdx::mem::make_shared<CrystalBarrier>();
            // case SubspaceTunnel::ID:
            //     return stdx::mem::make_shared<SubspaceTunnel>();
            // case DeltaField::ID:
            //     return stdx::mem::make_shared<DeltaField>();
            // case WhimsicalWindmill::ID:
            //     return stdx::mem::make_shared<WhimsicalWindmill>();
            // case AwakeningOfTalent::ID:
            //     return stdx::mem::make_shared<AwakeningOfTalent>();
            // case StarBlastingFuse::ID:
            //     return stdx::mem::make_shared<StarBlastingFuse>(); // Sets InvisibleBomb trap when activated
            // case MeltingMemories::ID:
            //     return stdx::mem::make_shared<MeltingMemories>();
            // case SantasJob::ID:
            //     return stdx::mem::make_shared<SantasJob>();
            // case AnotherUltimateWeapon::ID:
            //     return stdx::mem::make_shared<AnotherUltimateWeapon>();
            // case EvilSpyWorkPreparation::ID:
            //     return stdx::mem::make_shared<EvilSpyWorkPreparation>(); // Sets EvilSpyWorkExecution trap when activated
            // case WarudaMachineBlastOff::ID:
            //     return stdx::mem::make_shared<WarudaMachineBlastOff>();
            // case FinalSurgery::ID:
            //     return stdx::mem::make_shared<FinalSurgery>();
            // case 41:
            // case Overseer::ID:
            //     return stdx::mem::make_shared<Overseer>();
            // case WitchsHairLock::ID:
            //     return stdx::mem::make_shared<WitchsHairLock>();
            // case SolidWitch::ID:
            //     return stdx::mem::make_shared<SolidWitch>();
            // case EvilMastermind::ID:
            //     return stdx::mem::make_shared<EvilMastermind>();
            // case MiracleRedBeanIceCream::ID:
            //     return stdx::mem::make_shared<MiracleRedBeanIceCream>();
            // case MagicalRevenge::ID:
            //     return stdx::mem::make_shared<MagicalRevenge>();
            // case RevivalOfStars::ID:
            //     return stdx::mem::make_shared<RevivalOfStars>();
            // case StealthOn::ID:
            //     return stdx::mem::make_shared<StealthOn>();
            // case DoPiratesFlyInTheSky::ID:
            //     return stdx::mem::make_shared<DoPiratesFlyInTheSky>(); // Sets FlyingPirate trap when activated
            // case WhiteChristmasher::ID:
            //     return stdx::mem::make_shared<WhiteChristmasher>(); // Converts to TrueWhiteChristmasher when carrying RedAndBlue
            // case CookingTime::ID:
            //     return stdx::mem::make_shared<CookingTime>();
            // case MiracleWalker::ID:
            //     return stdx::mem::make_shared<MiracleWalker>();
            // case BranchExplosionStrategy::ID:
            //     return stdx::mem::make_shared<BranchExplosionStrategy>(); // Converts all cards to RbitHobbyShop
            // case ExtendedPhotonRifle::ID:
            //     return stdx::mem::make_shared<ExtendedPhotonRifle>();
            // case LeapThroughSpaceMarking::ID:
            //     return stdx::mem::make_shared<LeapThroughSpaceMarking>(); // Converts to LeapThroughSpace when activated
            // case SpecialStage::ID:
            //     return stdx::mem::make_shared<SpecialStage>();
            // case YuukiHand::ID:
            //     return stdx::mem::make_shared<YuukiHand>(); // Alternates between AngelHand (even chapters) and DevilHand (odd chapters)
            // case Rival::ID:
            //     return stdx::mem::make_shared<Rival>();
            // case ObserverOfEternity::ID:
            //     return stdx::mem::make_shared<ObserverOfEternity>();
            // case ReproductionOfRecords::ID:
            //     return stdx::mem::make_shared<ReproductionOfRecords>();
            // case ElliesMiracle::ID:
            //     return stdx::mem::make_shared<ElliesMiracle>();
            // case LulusLuckyEgg::ID:
            //     return stdx::mem::make_shared<LulusLuckyEgg>();
            // case RocketCannon::ID:
            //     return stdx::mem::make_shared<RocketCannon>(); // Converts to BigRocketCannon if alternate effect is used
            // case FullSpeedAlicianrone::ID:
            //     return stdx::mem::make_shared<FullSpeedAlicianrone>();
            // case BeastWitch::ID:
            //     return stdx::mem::make_shared<BeastWitch>();
            // case IntelligenceOfficer::ID:
            //     return stdx::mem::make_shared<IntelligenceOfficer>();
            // case RagingMadness::ID:
            //     return stdx::mem::make_shared<RagingMadness>();
            // case SaintEyes::ID:
            //     return stdx::mem::make_shared<SaintEyes>();
            // case ChefICouldUseSomeHelp::ID:
            //     return stdx::mem::make_shared<ChefICouldUseSomeHelp>(); // Converts to ManagerICouldUseSomeHelp when having 4 or more store manager counters and at least level 4
            // case SafeJourney::ID:
            //     return stdx::mem::make_shared<SafeJourney>();
            // case GuidanceOfTheWeathercock::ID:
            //     return stdx::mem::make_shared<GuidanceOfTheWeathercock>();
            // case Upshift::ID:
            //     return stdx::mem::make_shared<Upshift>();
            // case ZealousSalesman::ID:
            //     return stdx::mem::make_shared<ZealousSalesman>();
            // case DanceInTheMoonlitNight::ID:
            //     return stdx::mem::make_shared<DanceInTheMoonlitNight>();
            // case NewNobility::ID:
            //     return stdx::mem::make_shared<NewNobility>(); // Converts to Affluence if held by FernetNoble
            // case TwilightColoredDream::ID:
            //     return stdx::mem::make_shared<TwilightColoredDream>();
            // case LittleMagnum::ID:
            //     return stdx::mem::make_shared<LittleMagnum>();
            // case IdealWorld::ID:
            //     return stdx::mem::make_shared<IdealWorld>();
            // case StarCollector::ID:
            //     return stdx::mem::make_shared<StarCollector>();
            // case TorrentOfMagic::ID:
            //     return stdx::mem::make_shared<TorrentOfMagic>();
            // case GoodestBoy::ID:
            //     return stdx::mem::make_shared<GoodestBoy>();
            // case SweetParadise::ID:
            //     return stdx::mem::make_shared<SweetParadise>(); // Sets SweetIndulgence trap when activated
            // case SweetMakersMagic::ID:
            //     return stdx::mem::make_shared<SweetMakersMagic>();
            // case OperationAMountainOfSweets::ID:
            //     return stdx::mem::make_shared<OperationAMountainOfSweets>();
            // case ThreatsToMySlumber::ID:
            //     return stdx::mem::make_shared<ThreatsToMySlumber>(); // Converts to WhenMySlumberBreaks when activated
            // case MakeBelievePrisonBreak::ID:
            //     return stdx::mem::make_shared<MakeBelievePrisonBreak>();
            // case MotherPower::ID:
            //     return stdx::mem::make_shared<MotherPower>();
            // case LuluIsAnUnluckyDragon::ID:
            //     return stdx::mem::make_shared<LuluIsAnUnluckyDragon>();
            // case ElliesHyperMiracle::ID:
            //     return stdx::mem::make_shared<ElliesHyperMiracle>();
            // case ExProtagonistsMomentOfGlory::ID:
            //     return stdx::mem::make_shared<ExProtagonistsMomentOfGlory>();
            // case AllGunsAtTheReady::ID:
            //     return stdx::mem::make_shared<AllGunsAtTheReady>();
            // case HeartOfResistance::ID:
            //     return stdx::mem::make_shared<HeartOfResistance>();
            // case SuperYouthTime::ID:
            //     return stdx::mem::make_shared<SuperYouthTime>();
            // case IllGetALittleIntoIt::ID:
            //     return stdx::mem::make_shared<IllGetALittleIntoIt>();
            // case HypeBringer::ID:
            //     return stdx::mem::make_shared<HypeBringer>();
            // case IntellectualSoundingBluff::ID:
            //     return stdx::mem::make_shared<IntellectualSoundingBluff>();
            // === All cards released from 3.28.1 onwards ===
            // case 98:
            //     return stdx::mem::make_shared<PreciseDiceRolls>();
            // === Hyper cards part of another hyper card ===
            // case DanceLongHairedBeasts::ID:
            //     return stdx::mem::make_shared<DanceLongHairedBeasts>();
            // case InvisibleBomb::ID:
            //     return stdx::mem::make_shared<InvisibleBomb>();
            // case EvilSpyWorkExecution::ID:
            //     return stdx::mem::make_shared<EvilSpyWorkExecution>();
            // case FlyingPirate::ID:
            //     return stdx::mem::make_shared<FlyingPirate>();
            // case TrueWhiteChristmasher::ID:
            //     return stdx::mem::make_shared<TrueWhiteChristmasher>();
            // case RbitHobbyShop::ID:
            //     return stdx::mem::make_shared<RbitHobbyShop>();
            // case LeapThroughSpace::ID:
            //     return stdx::mem::make_shared<LeapThroughSpace>();
            // case AngelHand::ID:
            //     return stdx::mem::make_shared<AngelHand>();
            // case DevilHand::ID:
            //     return stdx::mem::make_shared<DevilHand>();
            // case BigRocketCannon::ID:
            //     return stdx::mem::make_shared<BigRocketCannon>();
            // case ManagerICouldUseSomeHelp::ID:
            //     return stdx::mem::make_shared<ManagerICouldUseSomeHelp>();
            // case Affluence::ID:
            //     return stdx::mem::make_shared<Affluence>();
            // case SweetIndulgence::ID:
            //     return stdx::mem::make_shared<SweetIndulgence>();
            // case WhenMySlumberBreaks::ID:
            //     return stdx::mem::make_shared<WhenMySlumberBreaks>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
