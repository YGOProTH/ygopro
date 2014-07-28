#ifndef _BUILD_SCENE_H_
#define _BUILD_SCENE_H_

#include <set>

#include "deck_data.h"
#include "scene_mgr.h"
#include "gui_extra.h"

namespace ygopro
{
    
    struct BuilderCard : public DeckCardExtraData {
        unsigned int buffer_index = 0;
        CardTextureInfo card_tex;
        float moving_time_b = 0.0f;
        float moving_time_e = 0.0f;
        float fading_time_b = 0.0f;
        float fading_time_e = 0.0f;
        glbase::vector2<float> pos = {0.0f, 0.0f};
        glbase::vector2<float> size = {0.0f, 0.0f};
        glbase::vector2<float> start_pos = {0.0f, 0.0f};
        glbase::vector2<float> start_size = {0.0f, 0.0f};
        glbase::vector2<float> dest_pos = {0.0f, 0.0f};
        glbase::vector2<float> dest_size = {0.0f, 0.0f};
        float hl = 0.0f;
        float start_hl = 0.0f;
        float dest_hl = 1.0f;
        bool update_pos = false;
        bool update_color = false;
        bool show_limit = true;
        bool show_exclusive = true;
    };
    
    class BuildScene : public Scene {
    public:
        BuildScene();
        virtual ~BuildScene();
        virtual void Activate();
        virtual void Update();
        virtual void Draw();
        virtual void SetSceneSize(glbase::vector2<int> sz);
        virtual void MouseMove(sf::Event::MouseMoveEvent evt);
        virtual void MouseButtonDown(sf::Event::MouseButtonEvent evt);
        virtual void MouseButtonUp(sf::Event::MouseButtonEvent evt);
        virtual void KeyDown(sf::Event::KeyEvent evt);
        virtual void KeyUp(sf::Event::KeyEvent evt);
        
        void SetCardInfo(unsigned int code);
        void AddCard(unsigned int code, unsigned int pos);
        void StopViewRegulation() { view_regulation = 0; }
        
        void ClearDeck();
        void SortDeck();
        void ShuffleDeck();
        void SetDeckDirty();
        void LoadDeckFromFile(const std::wstring& file);
        void LoadDeckFromClipboard();
        void SaveDeckToFile(const std::wstring& file);
        void SaveDeckToClipboard();
        
        void UpdateBackGround();
        void UpdateCard();
        void UpdateAllCard();
        void RefreshAllCard();
        
        void RefreshCardPos(DeckCardData& dcd);
        void RefreshHL(DeckCardData& dcd);
        void RefreshLimit(DeckCardData& dcd);
        void RefreshEx(DeckCardData& dcd);
        void MoveTo(DeckCardData& dcd, float tm, glbase::vector2<float> dst, glbase::vector2<float> dsz);
        void ChangeHL(DeckCardData& dcd, float tm, float desthl);
        void ChangeExclusive(bool check);
        void ChangeRegulation(int index);
        void ViewRegulation(int limit);
        
        DeckCardData* GetCard(int pos, int index);
        std::tuple<int, int, int> GetHoverCard(float x, float y);
        
    protected:
        unsigned int index_buffer = 0;
        unsigned int deck_buffer = 0;
        unsigned int back_buffer = 0;
        unsigned int misc_buffer = 0;
        bool update_bg = true;
        bool update_card = true;
        std::wstring current_file;
        int view_regulation = 0;
        DeckData current_deck;
        glbase::vector2<int> scene_size = {0, 0};
        int max_row_count = 0;
        int main_row_count = 0;
        glbase::vector2<float> card_size = {0.0f, 0.0f};
        glbase::vector2<float> icon_size = {0.0f, 0.0f};
        float minx = 0.0f;
        float maxx = 0.0f;
        float main_y_spacing = 0.0f;
        float offsety[3] = {0.0f, 0.0f, 0.0f};
        float dx[3] = {0.0f, 0.0f, 0.0f};
        bool deck_edited = false;
        bool show_exclusive = true;
        std::array<TextureInfo<4>, 3> limit;
        std::array<TextureInfo<4>, 3> pool;
        TextureInfo<4> hmask;
        std::set<DeckCardData*> updating_cards;
        std::weak_ptr<sgui::SGIconLabel> deck_label;
        std::shared_ptr<FileDialog> file_dialog;
        std::shared_ptr<FilterDialog> filter_dialog;
    };
    
}
#endif