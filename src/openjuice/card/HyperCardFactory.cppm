/**
 * @file HyperCardFactory.cppm
 * @module openjuice.card.HyperCardFactory
 * @brief Implementation of the HyperCardFactory class.
 *
 * This file contains the implementation of the HyperCardFactory class, which is used to create HyperCard objects.
 */

module;

#include "Macros.hpp"
#include "Rename.hpp"

export module openjuice.card.HyperCardFactory;

import std;
import stdx;

import openjuice.engine.card.Card;
import openjuice.engine.card.SpawnTypes;
import openjuice.engine.managers.GlobalSettings;
import openjuice.card.hyper;

using std::mem::SharedPointer;
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
                return std::mem::make_shared<ProtagonistsPrivilege>();
            case X16BigRocket::ID:
                return std::mem::make_shared<X16BigRocket>();
            case HyperMode::ID:
                return std::mem::make_shared<HyperMode>();
            case Accelerator::ID:
                return std::mem::make_shared<Accelerator>();
            // === Unlockable character hyper cards ===
            case PresentForYou::ID:
                return std::mem::make_shared<PresentForYou>();
            case AirStrike::ID:
                return std::mem::make_shared<AirStrike>();
            case BindingChains::ID:
                return std::mem::make_shared<BindingChains>();
            case Ubiquitous::ID:
                return std::mem::make_shared<Ubiquitous>();
            case MagicalInferno::ID:
                return std::mem::make_shared<MagicalInferno>();
            case ChristmasInferno::ID:
                return std::mem::make_shared<ChristmasInferno>();
            case BlueCrowTheSecond::ID:
                return std::mem::make_shared<BlueCrowTheSecond>();
            case ExtraordinarySpecs::ID:
                return std::mem::make_shared<ExtraordinarySpecs>();
            case MagicalMassacre::ID:
                return std::mem::make_shared<MagicalMassacre>();
            case Gamble::ID:
                return std::mem::make_shared<Gamble>();
            // === Store-unlocked character hyper cards ===
            // case GoldenEgg::ID:
            //     return std::mem::make_shared<GoldenEgg>();
            // case ReflectiveShell::ID:
            //     return std::mem::make_shared<ReflectiveShell>();
            // case JonathanRush::ID:
            //     return std::mem::make_shared<JonathanRush>();
            // case BannedForLife::ID:
            //     return std::mem::make_shared<BannedForLife>();
            // case TurboCharged::ID:
            //     return std::mem::make_shared<TurboCharged>();
            // case ImmovableObject::ID:
            //     return std::mem::make_shared<ImmovableObject>();
            // === DLC-unlocked character hyper cards ===
            // case BeyondHell::ID:
            //     return std::mem::make_shared<BeyondHell>();
            // case DeployBits::ID:
            //     return std::mem::make_shared<DeployBits>();
            // case SweetGuardian::ID:
            //     return std::mem::make_shared<SweetGuardian>();
            // case BigBangBell::ID:
            //     return std::mem::make_shared<BigBangBell>();
            // case CastOff::ID:
            //     return std::mem::make_shared<CastOff>();
            // case PlushieMaster::ID:
            //     return std::mem::make_shared<PlushieMaster>(); // Sets DanceLongEaredBeasts trap when activated
            // case Blazing::ID:
            //     return std::mem::make_shared<Blazing>();
            // case SelfDestruct::ID:
            //     return std::mem::make_shared<SelfDestruct>();
            // case CrystalBarrier::ID:
            //     return std::mem::make_shared<CrystalBarrier>();
            // case SubspaceTunnel::ID:
            //     return std::mem::make_shared<SubspaceTunnel>();
            // case DeltaField::ID:
            //     return std::mem::make_shared<DeltaField>();
            // case WhimsicalWindmill::ID:
            //     return std::mem::make_shared<WhimsicalWindmill>();
            // case AwakeningOfTalent::ID:
            //     return std::mem::make_shared<AwakeningOfTalent>();
            // case StarBlastingFuse::ID:
            //     return std::mem::make_shared<StarBlastingFuse>(); // Sets InvisibleBomb trap when activated
            // case MeltingMemories::ID:
            //     return std::mem::make_shared<MeltingMemories>();
            // case SantasJob::ID:
            //     return std::mem::make_shared<SantasJob>();
            // case AnotherUltimateWeapon::ID:
            //     return std::mem::make_shared<AnotherUltimateWeapon>();
            // case EvilSpyWorkPreparation::ID:
            //     return std::mem::make_shared<EvilSpyWorkPreparation>(); // Sets EvilSpyWorkExecution trap when activated
            // case WarudaMachineBlastOff::ID:
            //     return std::mem::make_shared<WarudaMachineBlastOff>();
            // case FinalSurgery::ID:
            //     return std::mem::make_shared<FinalSurgery>();
            // case 41:
            // case Overseer::ID:
            //     return std::mem::make_shared<Overseer>();
            // case WitchsHairLock::ID:
            //     return std::mem::make_shared<WitchsHairLock>();
            // case SolidWitch::ID:
            //     return std::mem::make_shared<SolidWitch>();
            // case EvilMastermind::ID:
            //     return std::mem::make_shared<EvilMastermind>();
            // case MiracleRedBeanIceCream::ID:
            //     return std::mem::make_shared<MiracleRedBeanIceCream>();
            // case MagicalRevenge::ID:
            //     return std::mem::make_shared<MagicalRevenge>();
            // case RevivalOfStars::ID:
            //     return std::mem::make_shared<RevivalOfStars>();
            // case StealthOn::ID:
            //     return std::mem::make_shared<StealthOn>();
            // case DoPiratesFlyInTheSky::ID:
            //     return std::mem::make_shared<DoPiratesFlyInTheSky>(); // Sets FlyingPirate trap when activated
            // case WhiteChristmasher::ID:
            //     return std::mem::make_shared<WhiteChristmasher>(); // Converts to TrueWhiteChristmasher when carrying RedAndBlue
            // case CookingTime::ID:
            //     return std::mem::make_shared<CookingTime>();
            // case MiracleWalker::ID:
            //     return std::mem::make_shared<MiracleWalker>();
            // case BranchExplosionStrategy::ID:
            //     return std::mem::make_shared<BranchExplosionStrategy>(); // Converts all cards to RbitHobbyShop
            // case ExtendedPhotonRifle::ID:
            //     return std::mem::make_shared<ExtendedPhotonRifle>();
            // case LeapThroughSpaceMarking::ID:
            //     return std::mem::make_shared<LeapThroughSpaceMarking>(); // Converts to LeapThroughSpace when activated
            // case SpecialStage::ID:
            //     return std::mem::make_shared<SpecialStage>();
            // case YuukiHand::ID:
            //     return std::mem::make_shared<YuukiHand>(); // Alternates between AngelHand (even chapters) and DevilHand (odd chapters)
            // case Rival::ID:
            //     return std::mem::make_shared<Rival>();
            // case ObserverOfEternity::ID:
            //     return std::mem::make_shared<ObserverOfEternity>();
            // case ReproductionOfRecords::ID:
            //     return std::mem::make_shared<ReproductionOfRecords>();
            // case ElliesMiracle::ID:
            //     return std::mem::make_shared<ElliesMiracle>();
            // case LulusLuckyEgg::ID:
            //     return std::mem::make_shared<LulusLuckyEgg>();
            // case RocketCannon::ID:
            //     return std::mem::make_shared<RocketCannon>(); // Converts to BigRocketCannon if alternate effect is used
            // case FullSpeedAlicianrone::ID:
            //     return std::mem::make_shared<FullSpeedAlicianrone>();
            // case BeastWitch::ID:
            //     return std::mem::make_shared<BeastWitch>();
            // case IntelligenceOfficer::ID:
            //     return std::mem::make_shared<IntelligenceOfficer>();
            // case RagingMadness::ID:
            //     return std::mem::make_shared<RagingMadness>();
            // case SaintEyes::ID:
            //     return std::mem::make_shared<SaintEyes>();
            // case ChefICouldUseSomeHelp::ID:
            //     return std::mem::make_shared<ChefICouldUseSomeHelp>(); // Converts to ManagerICouldUseSomeHelp when having 4 or more store manager counters and at least level 4
            // case SafeJourney::ID:
            //     return std::mem::make_shared<SafeJourney>();
            // case GuidanceOfTheWeathercock::ID:
            //     return std::mem::make_shared<GuidanceOfTheWeathercock>();
            // case Upshift::ID:
            //     return std::mem::make_shared<Upshift>();
            // case ZealousSalesman::ID:
            //     return std::mem::make_shared<ZealousSalesman>();
            // case DanceInTheMoonlitNight::ID:
            //     return std::mem::make_shared<DanceInTheMoonlitNight>();
            // case NewNobility::ID:
            //     return std::mem::make_shared<NewNobility>(); // Converts to Affluence if held by FernetNoble
            // case TwilightColoredDream::ID:
            //     return std::mem::make_shared<TwilightColoredDream>();
            // case LittleMagnum::ID:
            //     return std::mem::make_shared<LittleMagnum>();
            // case IdealWorld::ID:
            //     return std::mem::make_shared<IdealWorld>();
            // case StarCollector::ID:
            //     return std::mem::make_shared<StarCollector>();
            // case TorrentOfMagic::ID:
            //     return std::mem::make_shared<TorrentOfMagic>();
            // case GoodestBoy::ID:
            //     return std::mem::make_shared<GoodestBoy>();
            // case SweetParadise::ID:
            //     return std::mem::make_shared<SweetParadise>(); // Sets SweetIndulgence trap when activated
            // case SweetMakersMagic::ID:
            //     return std::mem::make_shared<SweetMakersMagic>();
            // case OperationAMountainOfSweets::ID:
            //     return std::mem::make_shared<OperationAMountainOfSweets>();
            // case ThreatsToMySlumber::ID:
            //     return std::mem::make_shared<ThreatsToMySlumber>(); // Converts to WhenMySlumberBreaks when activated
            // case MakeBelievePrisonBreak::ID:
            //     return std::mem::make_shared<MakeBelievePrisonBreak>();
            // case MotherPower::ID:
            //     return std::mem::make_shared<MotherPower>();
            // case LuluIsAnUnluckyDragon::ID:
            //     return std::mem::make_shared<LuluIsAnUnluckyDragon>();
            // case ElliesHyperMiracle::ID:
            //     return std::mem::make_shared<ElliesHyperMiracle>();
            // case ExProtagonistsMomentOfGlory::ID:
            //     return std::mem::make_shared<ExProtagonistsMomentOfGlory>();
            // case AllGunsAtTheReady::ID:
            //     return std::mem::make_shared<AllGunsAtTheReady>();
            // case HeartOfResistance::ID:
            //     return std::mem::make_shared<HeartOfResistance>();
            // case SuperYouthTime::ID:
            //     return std::mem::make_shared<SuperYouthTime>();
            // case IllGetALittleIntoIt::ID:
            //     return std::mem::make_shared<IllGetALittleIntoIt>();
            // case HypeBringer::ID:
            //     return std::mem::make_shared<HypeBringer>();
            // case IntellectualSoundingBluff::ID:
            //     return std::mem::make_shared<IntellectualSoundingBluff>();
            // === All cards released from 3.28.1 onwards ===
            // case 98:
            //     return std::mem::make_shared<PreciseDiceRolls>();
            // === Hyper cards part of another hyper card ===
            // case DanceLongHairedBeasts::ID:
            //     return std::mem::make_shared<DanceLongHairedBeasts>();
            // case InvisibleBomb::ID:
            //     return std::mem::make_shared<InvisibleBomb>();
            // case EvilSpyWorkExecution::ID:
            //     return std::mem::make_shared<EvilSpyWorkExecution>();
            // case FlyingPirate::ID:
            //     return std::mem::make_shared<FlyingPirate>();
            // case TrueWhiteChristmasher::ID:
            //     return std::mem::make_shared<TrueWhiteChristmasher>();
            // case RbitHobbyShop::ID:
            //     return std::mem::make_shared<RbitHobbyShop>();
            // case LeapThroughSpace::ID:
            //     return std::mem::make_shared<LeapThroughSpace>();
            // case AngelHand::ID:
            //     return std::mem::make_shared<AngelHand>();
            // case DevilHand::ID:
            //     return std::mem::make_shared<DevilHand>();
            // case BigRocketCannon::ID:
            //     return std::mem::make_shared<BigRocketCannon>();
            // case ManagerICouldUseSomeHelp::ID:
            //     return std::mem::make_shared<ManagerICouldUseSomeHelp>();
            // case Affluence::ID:
            //     return std::mem::make_shared<Affluence>();
            // case SweetIndulgence::ID:
            //     return std::mem::make_shared<SweetIndulgence>();
            // case WhenMySlumberBreaks::ID:
            //     return std::mem::make_shared<WhenMySlumberBreaks>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
