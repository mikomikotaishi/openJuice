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

import openjuice.engine.unit;
import openjuice.engine.util;
import openjuice.unit.characters;

using stdx::mem::Pointers;
using stdx::mem::SharedPointer;

using namespace openjuice::engine::unit;
using namespace openjuice::unit::characters::main::base;
// using namespace openjuice::unit::characters::main::bonus;
// using namespace openjuice::unit::characters::main::dlc1;
// using namespace openjuice::unit::characters::main::dlc2;
// using namespace openjuice::unit::characters::main::dlc3;
// using namespace openjuice::unit::characters::main::dlc4;
// using namespace openjuice::unit::characters::main::dlc5;

BEGIN_MODULE_NAMESPACE(openjuice::unit);

/**
 * @class CharacterFactory
 * @brief Factory class for creating Playable objects.
 *
 * The CharacterFactory class is a singleton factory class that creates Playable objects based on the given ID.
 */
export class CharacterFactory final {
public:
    CharacterFactory() = delete("CharacterFactory is a utility class and cannot be instantiated.");

    /**
     * @brief Get the ID of a Playable from its name.
     * @param name Name of the Playable
     * @return Optional containing the ID of the Playable, or nullopt if not found
     */
    [[nodiscard]]
    static constexpr Optional<u8> idOf(StringView name) noexcept {
        switch (engine::util::hashString(name)) {
            case "Kai"_hash:
                return Kai::ID;
            case "Marc"_hash:
                return Marc::ID;
            case "QP"_hash:
                return QP::ID;
            case "Suguri"_hash:
                return Suguri::ID;
            case "Aru"_hash:
                return Aru::ID;
            case "Fernet"_hash:
                return Fernet::ID;
            case "Hime"_hash:
                return Hime::ID;
            case "Marie Poppo"_hash:
                return MariePoppo::ID;
            case "Mio"_hash:
                return Mio::ID;
            case "Mio (Festive)"_hash:
                return MioFestive::ID;
            case "Peat"_hash:
                return Peat::ID;
            case "Sora"_hash:
                return Sora::ID;
            case "Tomomo"_hash:
                return Tomomo::ID;
            case "Yuki"_hash:
                return Yuki::ID;
            // case "Chicken"_hash:
            //     return Chicken::ID;
            // case "Robo Ball"_hash:
            //     return RoboBall::ID;
            // case "Seagull"_hash:
            //     return Seagull::ID;
            // case "Store Manager"_hash:
            //     return StoreManager::ID;
            // case "Shifu Robot"_hash:
            //     return ShifuRobot::ID;
            // case "Flying Castle"_hash:
            //     return FlyingCastle::ID;
            // case "Syura"_hash:
            //     return Syura::ID;
            // case "Nanako"_hash:
            //     return Nanako::ID;
            // case "QP (Dangerous)"_hash:
            //     return QPDangerous::ID;
            // case "Saki"_hash:
            //     return Saki::ID;
            // case "Kyousuke"_hash:
            //     return Kyousuke::ID;
            // case "Krilalaris"_hash:
            //     return Krilalaris::ID;
            // case "Kae"_hash:
            //     return Kae::ID;
            // case "Alte"_hash:
            //     return Alte::ID;
            // case "Kyoko"_hash:
            //     return Kyoko::ID;
            // case "Marie Poppo (Mixed)"_hash:
            //     return MariePoppoMixed::ID;
            // case "Sham"_hash:
            //     return Sham::ID;
            // case "Sherry"_hash:
            //     return Sherry::ID;
            // case "Sora (Military)"_hash:
            //     return SoraMilitary::ID;
            // case "Star Breaker"_hash:
            //     return StarBreaker::ID;
            // case "Sweet Breaker"_hash:
            //     return SweetBreaker::ID;
            // case "Aru (Scramble)"_hash:
            //     return AruScramble::ID;
            // case "Nath"_hash:
            //     return Nath::ID;
            // case "Tomato"_hash:
            //     return Tomato::ID;
            // case "Mimyuu"_hash:
            //     return Mimyuu::ID;
            // case "Kiriko"_hash:
            //     return Kiriko::ID;
            // case "NoName"_hash:
            //     return NoName::ID;
            // case "NoName (Head)"_hash:
            //     return NoNameHead::ID;
            // case "Ceoreparque"_hash:
            //     return Ceoreparque::ID;
            // case "Miusaki"_hash:
            //     return Miusaki::ID;
            // case "Yuki (Dangerous)"_hash:
            //     return YukiDangerous::ID;
            // case "Tomomo (Casual)"_hash:
            //     return TomomoCasual::ID;
            // case "Tomomo (Sweet Eater)"_hash:
            //     return TomomoSweetEater::ID;
            // case "Suguri (Ver.2)"_hash:
            //    return SuguriVer2::ID;
            // case "Tsih"_hash:
            //     return Tsih::ID;
            // case "Tequila"_hash:
            //     return Tequila::ID;
            // case "Mei"_hash:
            //     return Mei::ID;
            // case "Natsumi"_hash:
            //     return Natsumi::ID;
            // case "Arthur"_hash:
            //     return Arthur::ID;
            // case "Iru"_hash:
            //     return Iru::ID;
            // case "Mira"_hash:
            //     return Mira::ID;
            // case "Cuties"_hash:
            //     return Cuties::ID;
            // case "Yuuki"_hash:
            //     return Yuuki::ID;
            // case "Islay"_hash:
            //     return Islay::ID;
            // case "Suguri (46 Billion Years)"_hash:
            //     return Suguri46BillionYears::ID;
            // case "Sumika"_hash:
            //     return Sumika::ID;
            // case "Ellie"_hash:
            //     return Ellie::ID;
            // case "Lulu"_hash:
            //     return Lulu::ID;
            // case "MarcPilot"_hash:
            //     return MarcPilot::ID;
            // case "Alicianrone"_hash:
            //     return Alicianrone::ID;
            // case "Teotoratta"_hash:
            //     return Teotoratta::ID;
            // case "Arnelle"_hash:
            //     return Arnelle::ID;
            // case "Maynie"_hash:
            //     return Maynie::ID;
            // case "Kyupita"_hash:
            //     return Kyupita::ID;
            // case "Chris"_hash:
            //     return Chris::ID;
            // case "Halena"_hash:
            //     return Halena::ID;
            // case "Cook"_hash:
            //     return Cook::ID;
            // case "Lone Rider"_hash:
            //     return LoneRider::ID;
            // case "Merchant"_hash:
            //     return Merchant::ID;
            // case "Hime (Moonlight)"_hash:
            //     return HimeMoonlight::ID;
            // case "Fernet (Noble)"_hash:
            //     return FernetNoble::ID;
            // case "Malt"_hash:
            //     return Malt::ID;
            // case "Mescal"_hash:
            //     return Mescal::ID;
            // case "Shifu"_hash:
            //     return Shifu::ID;
            // case "Hoshino Reika"_hash:
            //     return HoshinoReika::ID;
            // case "Watty"_hash:
            //     return Watty::ID;
            // case "Pomeranius"_hash:
            //     return Pomeranius::ID;
            // case "Sweet Creator"_hash:
            //     return SweetCreator::ID;
            // case "Saki (Sweet Maker)"_hash:
            //     return SakiSweetMaker::ID;
            // case "Natsumi (Sweet Blogger)"_hash:
            //     return NatsumiSweetBlogger::ID;
            // case "Krilalaris (Pajamas)"_hash:
            //     return KrilalarisPajamas::ID;
            // case "Mimyuu (Jailbird)"_hash:
            //     return MimyuuJailbird::ID;
            // case "Mother Poppo"_hash:
            //     return MotherPoppo::ID;
            // case "Dark Lulu"_hash:
            //     return DarkLulu::ID;
            // case "Hyper Ellie"_hash:
            //     return HyperEllie::ID;
            // case "Kai (Hero)"_hash:
            //     return KaiHero::ID;
            // case "Grain"_hash:
            //     return Grain::ID;
            // case "Bourbon"_hash:
            //     return Bourbon::ID;
            // case "Poyo"_hash:
            //     return Poyo::ID;
            // case "Chuu"_hash:
            //     return Chuu::ID;
            // case "Haruka"_hash:
            //     return Haruka::ID;
            // case "Kanata"_hash:
            //     return Kanata::ID;
            // case "Mari Popomi"_hash:
            //     return MariPopomi::ID;
            // case "Majikawa Mimomo"_hash:
            //     return MajikawaMimomo::ID;
            // case "Amatsukuri Kurie"_hash:
            //     return AmatsukuriKurie::ID;
            default:
                return nullopt;
        }
    }

    /**
     * @brief Create a Playable object with the given ID.
     * @param id ID of the Playable to create
     * @return Shared pointer to the created Playable object, or nullopt if invalid ID
     */
    [[nodiscard]]
    static constexpr Optional<SharedPointer<Playable>> create(u8 id) noexcept {
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
            // case MajikawaMimomo::ID:
            //     return Pointers::shared<MajikawaMimomo>();
            // case AmatsukuriKurie::ID:
            //     return Pointers::shared<AmatsukuriKurie>();
            default:
                return nullopt;
        }
    }
};

END_MODULE_NAMESPACE();
