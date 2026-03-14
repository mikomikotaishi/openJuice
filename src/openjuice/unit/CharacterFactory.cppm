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

import stdx;

import openjuice.engine.managers;
import openjuice.engine.unit;
import openjuice.unit.characters;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;
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
                return Pointers::shared<Kai>();
            case Marc::ID:
                return Pointers::shared<Marc>();
            case QP::ID:
                return Pointers::shared<QP>();
            case Suguri::ID:
                return Pointers::shared<Suguri>();
            // === Unlockable characters ===
            case Aru::ID:
                return Pointers::shared<Aru>();
            case Fernet::ID:
                return Pointers::shared<Fernet>();
            case Hime::ID:
                return Pointers::shared<Hime>();
            case MariePoppo::ID:
                return Pointers::shared<MariePoppo>();
            case Mio::ID:
                return Pointers::shared<Mio>();
            case MioFestive::ID:
                return Pointers::shared<MioFestive>();
            case Peat::ID:
                return Pointers::shared<Peat>();
            case Sora::ID:
                return Pointers::shared<Sora>();
            case Tomomo::ID:
                return Pointers::shared<Tomomo>();
            case Yuki::ID:
                return Pointers::shared<Yuki>();
            // // === Store-unlocked characters ===
            // case Chicken::ID:
            //     return Pointers::shared<Chicken>();
            // case RoboBall::ID:
            //     return Pointers::shared<RoboBall>();
            // case Seagull::ID:
            //     return Pointers::shared<Seagull>();
            // case StoreManager::ID:
            //     return Pointers::shared<StoreManager>();
            // case ShifuRobot::ID:
            //     return Pointers::shared<ShifuRobot>();
            // case FlyingCastle::ID:
            //     return Pointers::shared<FlyingCastle>();
            // === DLC-unlocked characters ===
            // case Syura::ID:
            //     return Pointers::shared<Syura>();
            // case Nanako::ID:
            //     return Pointers::shared<Nanako>();
            // case QPDangerous::ID:
            //     return Pointers::shared<QPDangerous>();
            // case Saki::ID:
            //     return Pointers::shared<Saki>();
            // case Kyousuke::ID:
            //     return Pointers::shared<Kyousuke>();
            // case Krilalaris::ID:
            //     return Pointers::shared<Krilalaris>();
            // case Kae::ID:
            //     return Pointers::shared<Kae>();
            // case Alte::ID:
            //     return Pointers::shared<Alte>();
            // case Kyoko::ID:
            //     return Pointers::shared<Kyoko>();
            // case MariePoppoMixed::ID:
            //     return Pointers::shared<MariePoppoMixed>();
            // case Sham::ID:
            //     return Pointers::shared<Sham>();
            // case Sherry::ID:
            //     return Pointers::shared<Sherry>();
            // case SoraMilitary::ID:
            //     return Pointers::shared<SoraMilitary>();
            // case StarBreaker::ID:
            //     return Pointers::shared<StarBreaker>();
            // case SweetBreaker::ID:
            //     return Pointers::shared<SweetBreaker>();
            // case AruScramble::ID:
            //     return Pointers::shared<AruScramble>();
            // case Nath::ID:
            //     return Pointers::shared<Nath>();
            // case Tomato::ID:
            //     return Pointers::shared<Tomato>();
            // case Mimyuu::ID:
            //     return Pointers::shared<Mimyuu>();
            // case Kiriko::ID:
            //     return Pointers::shared<Kiriko>();
            // case NoName::ID:
            //     return Pointers::shared<NoName>();
            // case NoNameHead::ID:
            //     return Pointers::shared<NoNameHead>();
            // case Ceoreparque::ID:
            //     return Pointers::shared<Ceoreparque>();
            // case Miusaki::ID:
            //     return Pointers::shared<Miusaki>();
            // case YukiDangerous::ID:
            //     return Pointers::shared<YukiDangerous>();
            // case TomomoCasual::ID:
            //     return Pointers::shared<TomomoCasual>();
            // case TomomoSweetEater::ID:
            //     return Pointers::shared<TomomoSweetEater>();
            // case SuguriVer2::ID:
            //     return Pointers::shared<SuguriVer2>();
            // case Tsih::ID:
            //     return Pointers::shared<Tsih>();
            // case Tequila::ID:
            //     return Pointers::shared<Tequila>();
            // case Mei::ID:
            //     return Pointers::shared<Mei>();
            // case Natsumi::ID:
            //     return Pointers::shared<Natsumi>();
            // case Nico::ID:
            //     return Pointers::shared<Nico>();
            // case Arthur::ID:
            //     return Pointers::shared<Arthur>();
            // case Iru::ID:
            //     return Pointers::shared<Iru>();
            // case Mira::ID:
            //     return Pointers::shared<Mira>();
            // case Cuties::ID:
            //     return Pointers::shared<Cuties>();
            // case Yuuki::ID:
            //     return Pointers::shared<Yuuki>();
            // case Islay::ID:
            //     return Pointers::shared<Islay>();
            // case Suguri46BillionYears::ID:
            //     return Pointers::shared<Suguri46BillionYears>();
            // case Sumika::ID:
            //     return Pointers::shared<Sumika>();
            // case Ellie::ID:
            //     return Pointers::shared<Ellie>();
            // case Lulu::ID:
            //     return Pointers::shared<Lulu>();
            // case MarcPilot::ID:
            //     return Pointers::shared<MarcPilot>();
            // case Alicianrone::ID:
            //     return Pointers::shared<Alicianrone>();
            // case Teotoratta::ID:
            //     return stdx::mem::make_shraed<Teotoratta>();
            // case Arnelle::ID:
            //     return Pointers::shared<Arnelle>();
            // case Maynie::ID:
            //     return Pointers::shared<Maynie>();
            // case Kyupita::ID:
            //     return Pointers::shared<Kyupita>();
            // case Chris::ID:
            //     return Pointers::shared<Chris>();
            // case Halena::ID:
            //     return Pointers::shared<Halena>();
            // case Cook::ID:
            //     return Pointers::shared<Cook>();
            // case LoneRider::ID:
            //     return Pointers::shared<LoneRider>();
            // case Merchant::ID:
            //     return Pointers::shared<Merchant>();
            // case HimeMoonlight::ID:
            //     return Pointers::shared<HimeMoonlight>();
            // case FernetNoble::ID:
            //     return Pointers::shared<FernetNoble>();
            // case Malt::ID:
            //     return Pointers::shared<Malt>();
            // case Mescal::ID:
            //     return Pointers::shared<Mescal>();
            // case Shifu::ID:
            //     return Pointers::shared<Shifu>();
            // case HoshinoReika::ID:
            //     return Pointers::shared<HoshinoReika>();
            // case Watty::ID:
            //     return Pointers::shared<Watty>();
            // case Pomeranius::ID:
            //     return Pointers::shared<Pomeranius>();
            // case SweetCreator::ID:
            //     return Pointers::shared<SweetCreator>();
            // case SakiSweetMaker::ID:
            //     return Pointers::shared<SakiSweetMaker>();
            // case NatsumiSweetBlogger::ID:
            //     return Pointers::shared<NatsumiSweetBlogger>();
            // case KrilalarisPajamas::ID:
            //     return Pointers::shared<KrilalarisPajamas>();
            // case MimyuuJailbird::ID:
            //     return Pointers::shared<MimyuuJailbird>();
            // case MotherPoppo::ID:
            //     return Pointers::shared<MotherPoppo>();
            // case DarkLulu::ID:
            //     return Pointers::shared<DarkLulu>();
            // case HyperEllie::ID:
            //     return Pointers::shared<HyperEllie>();
            // case KaiHero::ID:
            //     return Pointers::shared<KaiHero>();
            // case Grain::ID:
            //     return Pointers::shared<Grain>();
            // case Bourbon::ID:
            //     return Pointers::shared<Bourbon>();
            // case Poyo::ID:
            //     return Pointers::shared<Poyo>();
            // case Chuu::ID:
            //     return Pointers::shared<Chuu>();
            // case Haruka::ID:
            //     return Pointers::shared<Haruka>();
            // case Kanata::ID:
            //     return Pointers::shared<Kanata>();
            // === All characters released from 3.28.1 onwards ===
            // case MariPopomi::ID:
            //     return Pointers::shared<MariPopomi>();
            // case Kurie::ID:
            //     return Pointers::shared<Kurie>();
            // case Mimomo::ID:
            //     return Pointers::shared<Mimomo>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
