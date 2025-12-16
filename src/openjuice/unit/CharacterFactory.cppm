/**
 * @file CharacterFactory.cppm
 * @module openjuice.unit.CharacterFactory
 * @brief Implementation of the CharacterFactory class.
 *
 * This file contains the implementation of the CharacterFactory class, which is used to create Playable objects.
 */

module;

#include "Macros.hpp"

export module openjuice.unit.CharacterFactory;

import std;
import stdx;

import openjuice.engine.managers.GlobalSettings;
import openjuice.engine.unit.Playable;
import openjuice.unit.characters;

using std::mem::SharedPointer;
using stdx::util::logging::Logger;
using stdx::util::logging::LoggerFactory;

using namespace openjuice::engine::unit;
using namespace openjuice::unit::characters::maincharacters;

BEGIN_MODULE_NAMESPACE(openjuice::unit);

/**
 * @class CharacterFactory
 * @brief Factory class for creating Playable objects.
 *
 * The CharacterFactory class is a singleton factory class that creates Playable objects based on the given ID.
 */
export class CharacterFactory final {
private:
    UTILITY_CLASS(CharacterFactory);

    static inline const SharedPointer<Logger> LOGGER = LoggerFactory::instance().of("CharacterFactory"); ///< The logger instance.
public:
    /**
     * @brief Create a Playable object with the given ID.
     *
     * @param id ID of the Playable to create
     * @return Shared pointer to the created Playable object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static Optional<SharedPointer<Playable>> create(u8 id) noexcept {
        #ifndef NDEBUG
        LOGGER->debug("Creating Playable of ID: {}", id);
        #endif

        switch (id) {
            case 0:
                return nullptr;
            // === Main characters ===
            case 1:
                return std::mem::make_shared<Kai>();
            case 2:
                return std::mem::make_shared<Marc>();
            case 3:
                return std::mem::make_shared<QP>();
            case 4:
                return std::mem::make_shared<Suguri>();
            // === Unlockable characters ===
            case 5:
                return std::mem::make_shared<Aru>();
            case 6:
                return std::mem::make_shared<Fernet>();
            case 7:
                return std::mem::make_shared<Hime>();
            case 8:
                return std::mem::make_shared<MariePoppo>();
            case 9:
                return std::mem::make_shared<Mio>();
            case 10:
                return std::mem::make_shared<MioFestive>();
            case 11:
                return std::mem::make_shared<Peat>();
            case 12:
                return std::mem::make_shared<Sora>();
            case 13:
                return std::mem::make_shared<Tomomo>();
            case 14:
                return std::mem::make_shared<Yuki>();
            // // === Store-unlocked characters ===
            // case 15:
            //     return std::mem::make_shared<Chicken>();
            // case 16:
            //     return std::mem::make_shared<RoboBall>();
            // case 17:
            //     return std::mem::make_shared<Seagull>();
            // case 18:
            //     return std::mem::make_shared<StoreManager>();
            // case 19:
            //     return std::mem::make_shared<ShifuRobot>();
            // case 20:
            //     return std::mem::make_shared<FlyingCastle>();
            // === DLC-unlocked characters ===
            // case 21:
            //     return std::mem::make_shared<Syura>();
            // case 22:
            //     return std::mem::make_shared<Nanako>();
            // case 23:
            //     return std::mem::make_shared<QPDangerous>();
            // case 24:
            //     return std::mem::make_shared<Saki>();
            // case 25:
            //     return std::mem::make_shared<Kyousuke>();
            // case 26:
            //     return std::mem::make_shared<Krilalaris>();
            // case 27:
            //     return std::mem::make_shared<Kae>();
            // case 28:
            //     return std::mem::make_shared<Alte>();
            // case 29:
            //     return std::mem::make_shared<Kyoko>();
            // case 30:
            //     return std::mem::make_shared<MariePoppoMixed>();
            // case 31:
            //     return std::mem::make_shared<Sham>();
            // case 32:
            //     return std::mem::make_shared<Sherry>();
            // case 33:
            //     return std::mem::make_shared<SoraMilitary>();
            // case 34:
            //     return std::mem::make_shared<StarBreaker>();
            // case 35:
            //     return std::mem::make_shared<SweetBreaker>();
            // case 36:
            //     return std::mem::make_shared<AruScramble>();
            // case 37:
            //     return std::mem::make_shared<Nath>();
            // case 38:
            //     return std::mem::make_shared<Tomato>();
            // case 39:
            //     return std::mem::make_shared<Mimyuu>();
            // case 40:
            //     return std::mem::make_shared<Kiriko>();
            // case 41:
            //     return std::mem::make_shared<NoName>();
            // case 42:
            //     return std::mem::make_shared<NoNameHead>();
            // case 43:
            //     return std::mem::make_shared<Ceoreparque>();
            // case 44:
            //     return std::mem::make_shared<Miusaki>();
            // case 45:
            //     return std::mem::make_shared<YukiDangerous>();
            // case 46:
            //     return std::mem::make_shared<TomomoCasual>();
            // case 47:
            //     return std::mem::make_shared<TomomoSweetEater>();
            // case 48:
            //     return std::mem::make_shared<SuguriVer2>();
            // case 49:
            //     return std::mem::make_shared<Tsih>();
            // case 50:
            //     return std::mem::make_shared<Tequila>();
            // case 51:
            //     return std::mem::make_shared<Mei>();
            // case 52:
            //     return std::mem::make_shared<Natsumi>();
            // case 53:
            //     return std::mem::make_shared<Nico>();
            // case 54:
            //     return std::mem::make_shared<Arthur>();
            // case 55:
            //     return std::mem::make_shared<Iru>();
            // case 56:
            //     return std::mem::make_shared<Mira>();
            // case 57:
            //     return std::mem::make_shared<Cuties>();
            // case 58:
            //     return std::mem::make_shared<Yuuki>();
            // case 59:
            //     return std::mem::make_shared<Islay>();
            // case 60:
            //     return std::mem::make_shared<Suguri46BillionYears>();
            // case 61:
            //     return std::mem::make_shared<Sumika>();
            // case 62:
            //     return std::mem::make_shared<Ellie>();
            // case 63:
            //     return std::mem::make_shared<Lulu>();
            // case 64:
            //     return std::mem::make_shared<MarcPilot>();
            // case 65:
            //     return std::mem::make_shared<Alicianrone>();
            // case 66:
            //     return std::mem::make_shraed<Teotoratta>();
            // case 67:
            //     return std::mem::make_shared<Arnelle>();
            // case 68:
            //     return std::mem::make_shared<Maynie>();
            // case 69:
            //     return std::mem::make_shared<Kyupita>();
            // case 70:
            //     return std::mem::make_shared<Chris>();
            // case 71:
            //     return std::mem::make_shared<Halena>();
            // case 72:
            //     return std::mem::make_shared<Cook>();
            // case 73:
            //     return std::mem::make_shared<LoneRider>();
            // case 74:
            //     return std::mem::make_shared<Merchant>();
            // case 75:
            //     return std::mem::make_shared<HimeMoonlight>();
            // case 76:
            //     return std::mem::make_shared<FernetNoble>();
            // case 77:
            //     return std::mem::make_shared<Malt>();
            // case 78:
            //     return std::mem::make_shared<Mescal>();
            // case 79:
            //     return std::mem::make_shared<Shifu>();
            // case 80:
            //     return std::mem::make_shared<HoshinoReika>();
            // case 81:
            //     return std::mem::make_shared<Watty>();
            // case 82:
            //     return std::mem::make_shared<Pomeranius>();
            // case 83:
            //     return std::mem::make_shared<SweetCreator>();
            // case 84:
            //     return std::mem::make_shared<SakiSweetMaker>();
            // case 85:
            //     return std::mem::make_shared<NatsumiSweetBlogger>();
            // case 86:
            //     return std::mem::make_shared<KrilalarisPajamas>();
            // case 87:
            //     return std::mem::make_shared<MimyuuJailbird>();
            // case 88:
            //     return std::mem::make_shared<MotherPoppo>();
            // case 89:
            //     return std::mem::make_shared<DarkLulu>();
            // case 90:
            //     return std::mem::make_shared<HyperEllie>();
            // case 91:
            //     return std::mem::make_shared<KaiHero>();
            // case 92:
            //     return std::mem::make_shared<Grain>();
            // case 93:
            //     return std::mem::make_shared<Bourbon>();
            // case 94:
            //     return std::mem::make_shared<Poyo>();
            // case 95:
            //     return std::mem::make_shared<Chuu>();
            // case 96:
            //     return std::mem::make_shared<Haruka>();
            // case 97:
            //     return std::mem::make_shared<Kanata>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
