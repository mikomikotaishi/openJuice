/**
 * @file HyperCardFactory.cppm
 * @module openjuice.card.HyperCardFactory
 * @brief Implementation of the HyperCardFactory class.
 *
 * This file contains the implementation of the HyperCardFactory class, which is used to create HyperCard objects.
 */

module;

#include "Macros.hpp"

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

namespace fmt = std::fmt;
namespace mem = std::mem;

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
            case 1:
                return mem::make_shared<ProtagonistsPrivilege>();
            case 2:
                return mem::make_shared<X16BigRocket>();
            case 3:
                return mem::make_shared<HyperMode>();
            case 4:
                return mem::make_shared<Accelerator>();
            // === Unlockable character hyper cards ===
            case 5:
                return mem::make_shared<PresentForYou>();
            case 6:
                return mem::make_shared<AirStrike>();
            case 7:
                return mem::make_shared<BindingChains>();
            case 8:
                return mem::make_shared<Ubiquitous>();
            case 9:
                return mem::make_shared<MagicalInferno>();
            case 10:
                return mem::make_shared<ChristmasInferno>();
            case 11:
                return mem::make_shared<BlueCrowTheSecond>();
            case 12:
                return mem::make_shared<ExtraordinarySpecs>();
            case 13:
                return mem::make_shared<MagicalMassacre>();
            case 14:
                return mem::make_shared<Gamble>();
            // === Store-unlocked character hyper cards ===
            // case 15:
            //     return mem::make_shared<GoldenEgg>();
            // case 16:
            //     return mem::make_shared<ReflectiveShell>();
            // case 17:
            //     return mem::make_shared<JonathanRush>();
            // case 18:
            //     return mem::make_shared<BannedForLife>();
            // case 19:
            //     return mem::make_shared<TurboCharged>();
            // case 20:
            //     return mem::make_shared<ImmovableObject>();
            // === DLC-unlocked character hyper cards ===
            // case 21:
            //     return mem::make_shared<BeyondHell>();
            // case 22:
            //     return mem::make_shared<DeployBits>();
            // case 23:
            //     return mem::make_shared<SweetGuardian>();
            // case 24:
            //     return mem::make_shared<BigBangBell>();
            // case 25:
            //     return mem::make_shared<CastOff>();
            // case 26:
            //     return mem::make_shared<PlushieMaster>(); // Sets DanceLongEaredBeasts trap when activated
            // case 27:
            //     return mem::make_shared<Blazing>();
            // case 28:
            //     return mem::make_shared<SelfDestruct>();
            // case 29:
            //     return mem::make_shared<CrystalBarrier>();
            // case 30:
            //     return mem::make_shared<SubspaceTunnel>();
            // case 31:
            //     return mem::make_shared<DeltaField>();
            // case 32:
            //     return mem::make_shared<WhimsicalWindmill>();
            // case 33:
            //     return mem::make_shared<AwakeningOfTalent>();
            // case 34:
            //     return mem::make_shared<StarBlastingFuse>(); // Sets InvisibleBomb trap when activated
            // case 35:
            //     return mem::make_shared<MeltingMemories>();
            // case 36:
            //     return mem::make_shared<SantasJob>();
            // case 37:
            //     return mem::make_shared<AnotherUltimateWeapon>();
            // case 38:
            //     return mem::make_shared<EvilSpyWorkPreparation>(); // Sets EvilSpyWorkExecution trap when activated
            // case 39:
            //     return mem::make_shared<WarudaMachineBlastOff>();
            // case 40:
            //     return mem::make_shared<FinalSurgery>();
            // case 41:
            // case 42:
            //     return mem::make_shared<Overseer>();
            // case 43:
            //     return mem::make_shared<WitchsHairLock>();
            // case 44:
            //     return mem::make_shared<SolidWitch>();
            // case 45:
            //     return mem::make_shared<EvilMastermind>();
            // case 46:
            //     return mem::make_shared<MiracleRedBeanIceCream>();
            // case 47:
            //     return mem::make_shared<MagicalRevenge>();
            // case 48:
            //     return mem::make_shared<RevivalOfStars>();
            // case 49:
            //     return mem::make_shared<StealthOn>();
            // case 50:
            //     return mem::make_shared<DoPiratesFlyInTheSky>(); // Sets FlyingPirate trap when activated
            // case 51:
            //     return mem::make_shared<WhiteChristmasher>(); // Converts to TrueWhiteChristmasher when carrying RedAndBlue
            // case 52:
            //     return mem::make_shared<CookingTime>();
            // case 53:
            //     return mem::make_shared<MiracleWalker>();
            // case 54:
            //     return mem::make_shared<BranchExplosionStrategy>(); // Converts all cards to RbitHobbyShop
            // case 55:
            //     return mem::make_shared<ExtendedPhotonRifle>();
            // case 56:
            //     return mem::make_shared<LeapThroughSpaceMarking>(); // Converts to LeapThroughSpace when activated
            // case 57:
            //     return mem::make_shared<SpecialStage>();
            // case 58:
            //     return mem::make_shared<YuukiHand>(); // Alternates between AngelHand (even chapters) and DevilHand (odd chapters)
            // case 59:
            //     return mem::make_shared<Rival>();
            // case 60:
            //     return mem::make_shared<ObserverOfEternity>();
            // case 61:
            //     return mem::make_shared<ReproductionOfRecords>();
            // case 62:
            //     return mem::make_shared<ElliesMiracle>();
            // case 63:
            //     return mem::make_shared<LulusLuckyEgg>();
            // case 64:
            //     return mem::make_shared<RocketCannon>(); // Converts to BigRocketCannon if alternate effect is used
            // case 65:
            //     return mem::make_shared<FullSpeedAlicianrone>();
            // case 66:
            //     return mem::make_shared<BeastWitch>();
            // case 67:
            //     return mem::make_shared<IntelligenceOfficer>();
            // case 68:
            //     return mem::make_shared<RagingMadness>();
            // case 69:
            //     return mem::make_shared<SaintEyes>();
            // case 70:
            //     return mem::make_shared<ChefICouldUseSomeHelp>(); // Converts to ManagerICouldUseSomeHelp when having 4 or more store manager counters and at least level 4
            // case 71:
            //     return mem::make_shared<SafeJourney>();
            // case 72:
            //     return mem::make_shared<GuidanceOfTheWeathercock>();
            // case 73:
            //     return mem::make_shared<Upshift>();
            // case 74:
            //     return mem::make_shared<ZealousSalesman>();
            // case 75:
            //     return mem::make_shared<DanceInTheMoonlitNight>();
            // case 76:
            //     return mem::make_shared<NewNobility>(); // Converts to Affluence if held by FernetNoble
            // case 77:
            //     return mem::make_shared<TwilightColoredDream>();
            // case 78:
            //     return mem::make_shared<LittleMagnum>();
            // case 79:
            //     return mem::make_shared<IdealWorld>();
            // case 80:
            //     return mem::make_shared<StarCollector>();
            // case 81:
            //     return mem::make_shared<TorrentOfMagic>();
            // case 82:
            //     return mem::make_shared<GoodestBoy>();
            // case 83:
            //     return mem::make_shared<SweetParadise>(); // Sets SweetIndulgence trap when activated
            // case 84:
            //     return mem::make_shared<SweetMakersMagic>();
            // case 85:
            //     return mem::make_shared<OperationAMountainOfSweets>();
            // case 86:
            //     return mem::make_shared<ThreatsToMySlumber>(); // Converts to WhenMySlumberBreaks when activated
            // case 87:
            //     return mem::make_shared<MakeBelievePrisonBreak>();
            // case 88:
            //     return mem::make_shared<MotherPower>();
            // case 89:
            //     return mem::make_shared<LuluIsAnUnluckyDragon>();
            // case 90:
            //     return mem::make_shared<ElliesHyperMiracle>();
            // case 91:
            //     return mem::make_shared<ExProtagonistsMomentOfGlory>();
            // case 92:
            //     return mem::make_shared<AllGunsAtTheReady>();
            // case 93:
            //     return mem::make_shared<HeartOfResistance>();
            // case 94:
            //     return mem::make_shared<SuperYouthTime>();
            // case 95:
            //     return mem::make_shared<IllGetALittleIntoIt>();
            // case 96:
            //     return mem::make_shared<HypeBringer>();
            // case 97:
            //     return mem::make_shared<IntellectualSoundingBluff>();
            // case 1026:
            //     return mem::make_shared<DanceLongHairedBeasts>();
            // case 1034:
            //     return mem::make_shared<InvisibleBomb>();
            // case 1038:
            //     return mem::make_shared<EvilSpyWorkExecution>();
            // case 1050:
            //     return mem::make_shared<FlyingPirate>();
            // case 1051:
            //     return mem::make_shared<TrueWhiteChristmasher>();
            // case 1054:
            //     return mem::make_shared<RbitHobbyShop>();
            // case 1056:
            //     return mem::make_shared<LeapThroughSpace>();
            // case 1058:
            //     return mem::make_shared<AngelHand>();
            // case 1059:
            //     return mem::make_shared<DevilHand>();
            // case 1064:
            //     return mem::make_shared<BigRocketCannon>();
            // case 1070:
            //     return mem::make_shared<ManagerICouldUseSomeHelp>();
            // case 1076:
            //     return mem::make_shared<Affluence>();
            // case 1083:
            //     return mem::make_shared<SweetIndulgence>();
            // case 1086:
            //     return mem::make_shared<WhenMySlumberBreaks>();
            case 2001:
                return mem::make_shared<SeasonalUltimateWeaponInTheSun>();
            case 2002:
                return mem::make_shared<SeasonalLifeguardOnTheWhiteBeach>();
            case 2003:
                return mem::make_shared<SeasonalGuardianOfBloomingFlowers>();
            case 2004:
                return mem::make_shared<SeasonalUnforgivingAvenger>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
