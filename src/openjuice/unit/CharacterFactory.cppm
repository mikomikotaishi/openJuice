/**
 * @file CharacterFactory.cppm
 * @module openjuice.unit:CharacterFactory
 * @brief Implementation of the CharacterFactory class.
 *
 * This file contains the implementation of the CharacterFactory class, which is used to create Playable objects.
 */

module;

#include "Macros.hpp"

export module openjuice.unit:CharacterFactory;

import std;
import stdx;

import openjuice.engine.managers;
import openjuice.engine.unit;
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
            case Kai::ID:
                return std::mem::make_shared<Kai>();
            case Marc::ID:
                return std::mem::make_shared<Marc>();
            case QP::ID:
                return std::mem::make_shared<QP>();
            case Suguri::ID:
                return std::mem::make_shared<Suguri>();
            // === Unlockable characters ===
            case Aru::ID:
                return std::mem::make_shared<Aru>();
            case Fernet::ID:
                return std::mem::make_shared<Fernet>();
            case Hime::ID:
                return std::mem::make_shared<Hime>();
            case MariePoppo::ID:
                return std::mem::make_shared<MariePoppo>();
            case Mio::ID:
                return std::mem::make_shared<Mio>();
            case MioFestive::ID:
                return std::mem::make_shared<MioFestive>();
            case Peat::ID:
                return std::mem::make_shared<Peat>();
            case Sora::ID:
                return std::mem::make_shared<Sora>();
            case Tomomo::ID:
                return std::mem::make_shared<Tomomo>();
            case Yuki::ID:
                return std::mem::make_shared<Yuki>();
            // // === Store-unlocked characters ===
            // case Chicken::ID:
            //     return std::mem::make_shared<Chicken>();
            // case RoboBall::ID:
            //     return std::mem::make_shared<RoboBall>();
            // case Seagull::ID:
            //     return std::mem::make_shared<Seagull>();
            // case StoreManager::ID:
            //     return std::mem::make_shared<StoreManager>();
            // case ShifuRobot::ID:
            //     return std::mem::make_shared<ShifuRobot>();
            // case FlyingCastle::ID:
            //     return std::mem::make_shared<FlyingCastle>();
            // === DLC-unlocked characters ===
            // case Syura::ID:
            //     return std::mem::make_shared<Syura>();
            // case Nanako::ID:
            //     return std::mem::make_shared<Nanako>();
            // case QPDangerous::ID:
            //     return std::mem::make_shared<QPDangerous>();
            // case Saki::ID:
            //     return std::mem::make_shared<Saki>();
            // case Kyousuke::ID:
            //     return std::mem::make_shared<Kyousuke>();
            // case Krilalaris::ID:
            //     return std::mem::make_shared<Krilalaris>();
            // case Kae::ID:
            //     return std::mem::make_shared<Kae>();
            // case Alte::ID:
            //     return std::mem::make_shared<Alte>();
            // case Kyoko::ID:
            //     return std::mem::make_shared<Kyoko>();
            // case MariePoppoMixed::ID:
            //     return std::mem::make_shared<MariePoppoMixed>();
            // case Sham::ID:
            //     return std::mem::make_shared<Sham>();
            // case Sherry::ID:
            //     return std::mem::make_shared<Sherry>();
            // case SoraMilitary::ID:
            //     return std::mem::make_shared<SoraMilitary>();
            // case StarBreaker::ID:
            //     return std::mem::make_shared<StarBreaker>();
            // case SweetBreaker::ID:
            //     return std::mem::make_shared<SweetBreaker>();
            // case AruScramble::ID:
            //     return std::mem::make_shared<AruScramble>();
            // case Nath::ID:
            //     return std::mem::make_shared<Nath>();
            // case Tomato::ID:
            //     return std::mem::make_shared<Tomato>();
            // case Mimyuu::ID:
            //     return std::mem::make_shared<Mimyuu>();
            // case Kiriko::ID:
            //     return std::mem::make_shared<Kiriko>();
            // case NoName::ID:
            //     return std::mem::make_shared<NoName>();
            // case NoNameHead::ID:
            //     return std::mem::make_shared<NoNameHead>();
            // case Ceoreparque::ID:
            //     return std::mem::make_shared<Ceoreparque>();
            // case Miusaki::ID:
            //     return std::mem::make_shared<Miusaki>();
            // case YukiDangerous::ID:
            //     return std::mem::make_shared<YukiDangerous>();
            // case TomomoCasual::ID:
            //     return std::mem::make_shared<TomomoCasual>();
            // case TomomoSweetEater::ID:
            //     return std::mem::make_shared<TomomoSweetEater>();
            // case SuguriVer2::ID:
            //     return std::mem::make_shared<SuguriVer2>();
            // case Tsih::ID:
            //     return std::mem::make_shared<Tsih>();
            // case Tequila::ID:
            //     return std::mem::make_shared<Tequila>();
            // case Mei::ID:
            //     return std::mem::make_shared<Mei>();
            // case Natsumi::ID:
            //     return std::mem::make_shared<Natsumi>();
            // case Nico::ID:
            //     return std::mem::make_shared<Nico>();
            // case Arthur::ID:
            //     return std::mem::make_shared<Arthur>();
            // case Iru::ID:
            //     return std::mem::make_shared<Iru>();
            // case Mira::ID:
            //     return std::mem::make_shared<Mira>();
            // case Cuties::ID:
            //     return std::mem::make_shared<Cuties>();
            // case Yuuki::ID:
            //     return std::mem::make_shared<Yuuki>();
            // case Islay::ID:
            //     return std::mem::make_shared<Islay>();
            // case Suguri46BillionYears::ID:
            //     return std::mem::make_shared<Suguri46BillionYears>();
            // case Sumika::ID:
            //     return std::mem::make_shared<Sumika>();
            // case Ellie::ID:
            //     return std::mem::make_shared<Ellie>();
            // case Lulu::ID:
            //     return std::mem::make_shared<Lulu>();
            // case MarcPilot::ID:
            //     return std::mem::make_shared<MarcPilot>();
            // case Alicianrone::ID:
            //     return std::mem::make_shared<Alicianrone>();
            // case Teotoratta::ID:
            //     return std::mem::make_shraed<Teotoratta>();
            // case Arnelle::ID:
            //     return std::mem::make_shared<Arnelle>();
            // case Maynie::ID:
            //     return std::mem::make_shared<Maynie>();
            // case Kyupita::ID:
            //     return std::mem::make_shared<Kyupita>();
            // case Chris::ID:
            //     return std::mem::make_shared<Chris>();
            // case Halena::ID:
            //     return std::mem::make_shared<Halena>();
            // case Cook::ID:
            //     return std::mem::make_shared<Cook>();
            // case LoneRider::ID:
            //     return std::mem::make_shared<LoneRider>();
            // case Merchant::ID:
            //     return std::mem::make_shared<Merchant>();
            // case HimeMoonlight::ID:
            //     return std::mem::make_shared<HimeMoonlight>();
            // case FernetNoble::ID:
            //     return std::mem::make_shared<FernetNoble>();
            // case Malt::ID:
            //     return std::mem::make_shared<Malt>();
            // case Mescal::ID:
            //     return std::mem::make_shared<Mescal>();
            // case Shifu::ID:
            //     return std::mem::make_shared<Shifu>();
            // case HoshinoReika::ID:
            //     return std::mem::make_shared<HoshinoReika>();
            // case Watty::ID:
            //     return std::mem::make_shared<Watty>();
            // case Pomeranius::ID:
            //     return std::mem::make_shared<Pomeranius>();
            // case SweetCreator::ID:
            //     return std::mem::make_shared<SweetCreator>();
            // case SakiSweetMaker::ID:
            //     return std::mem::make_shared<SakiSweetMaker>();
            // case NatsumiSweetBlogger::ID:
            //     return std::mem::make_shared<NatsumiSweetBlogger>();
            // case KrilalarisPajamas::ID:
            //     return std::mem::make_shared<KrilalarisPajamas>();
            // case MimyuuJailbird::ID:
            //     return std::mem::make_shared<MimyuuJailbird>();
            // case MotherPoppo::ID:
            //     return std::mem::make_shared<MotherPoppo>();
            // case DarkLulu::ID:
            //     return std::mem::make_shared<DarkLulu>();
            // case HyperEllie::ID:
            //     return std::mem::make_shared<HyperEllie>();
            // case KaiHero::ID:
            //     return std::mem::make_shared<KaiHero>();
            // case Grain::ID:
            //     return std::mem::make_shared<Grain>();
            // case Bourbon::ID:
            //     return std::mem::make_shared<Bourbon>();
            // case Poyo::ID:
            //     return std::mem::make_shared<Poyo>();
            // case Chuu::ID:
            //     return std::mem::make_shared<Chuu>();
            // case Haruka::ID:
            //     return std::mem::make_shared<Haruka>();
            // case Kanata::ID:
            //     return std::mem::make_shared<Kanata>();
            // === All characters released from 3.28.1 onwards ===
            // case MariPopomi::ID:
            //     return std::mem::make_shared<MariPopomi>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
