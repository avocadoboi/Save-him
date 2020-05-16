#pragma once

#include "../Resources/Paths.hpp"
#include "../Resources/Words.hpp"
#include "App.hpp"
#include "GameOver.hpp"

#include <array>

//------------------------------

class DyingMan : public AvoGUI::View
{
public:
	inline static AvoGUI::Point<float> const SIZE{ 250.f, 250.f };
	static constexpr float DEATH_RATE = 1.f / 6.f;

private:
	float m_deathProgress = 0.f;
public:
	/*
		Returns true if the man is dead
	*/
	bool bringCloserToDeath()
	{
		m_deathProgress += DEATH_RATE;
		m_rock.setTop(m_deathProgress * (getHeight() - m_rock.getHeight()));
		m_man.setTop(AvoGUI::max(getHeight() - m_man.getHeight(), m_rock.getBottom()), false);
		invalidate();
		return m_deathProgress == 1.f;
	}

private:
	AvoGUI::Image m_man = getDrawingContext()->createImage(Paths::man);
	AvoGUI::Image m_rock = getDrawingContext()->createImage(Paths::rock);
public:
	// Will only be called at the beginning
	void handleSizeChange() override
	{
		m_rock.setCenterX(getWidth()*0.5f);
		m_rock.setTop(0.f);
		m_man.setCenterX(getWidth() * 0.5f);
		m_man.setBottom(getHeight());
	}

	//------------------------------

	void draw(AvoGUI::DrawingContext* p_context) override
	{
		p_context->drawImage(m_rock);
		p_context->drawImage(m_man);
	}

	//------------------------------

	DyingMan(AvoGUI::View* p_parent) :
		View(p_parent)
	{
		m_rock.setSize(m_rock.getSize() / 7.f);
		m_man.setSize(m_man.getSize() / 7.f);

		setSize(SIZE);
	}
};

//------------------------------

class GuessedWord : public AvoGUI::View
{
public:
	static constexpr float FONT_SIZE = 30.f;
	static constexpr float LETTER_HEIGHT = 34.f;
	static constexpr float LETTER_WIDTH = 30.f;

private:
	AvoGUI::Text m_underscore = getDrawingContext()->createText("_", FONT_SIZE);
	std::vector<AvoGUI::TextView*> m_letters;
public:
	void draw(AvoGUI::DrawingContext* p_context) override
	{
		p_context->setColor(Colors::onBackground);
		for (auto letter : m_letters)
		{
			m_underscore.setCenterX(letter->getCenterX());
			p_context->drawText(m_underscore);
		}
	}

private:
	uint32 m_numberOfLettersLeft;
public:
	/*
		Returns true if letter was found.
	*/
	bool guessLetter(char p_letter)
	{
		bool foundLetter = false;
		for (auto letter : m_letters)
		{
			if (letter->getText().getString()[0] == p_letter)
			{
				letter->setIsVisible(true);
				letter->setColor(Colors::primary);
				foundLetter = true;
				m_numberOfLettersLeft--;
			}
		}
		return foundLetter;
	}
	void showAllLetters()
	{
		for (auto letter : m_letters)
		{
			if (!letter->getIsVisible())
			{
				letter->setIsVisible(true);
				letter->setColor(Colors::onBackground);
			}
		}
	}

	bool getHasWon()
	{
		return m_numberOfLettersLeft == 0u;
	}

	GuessedWord(View* p_parent, float p_meanDifficulty, float p_standardDeviationDifficulty) :
		View{ p_parent }
	{
		enableMouseEvents();

		// Choose word

		int32 numberOfWords = sizeof(words) / sizeof(char const*);
		int32 index = numberOfWords * ((0.01f + 0.5f * p_standardDeviationDifficulty) * AvoGUI::randomNormal() + p_meanDifficulty);
		index = (index / numberOfWords & 1) == 0 ? std::abs(index % numberOfWords) : std::abs(numberOfWords - index % numberOfWords - 1);

		std::string word = words[index];

		m_numberOfLettersLeft = word.size();
		m_letters.reserve(word.size());

		for (auto character : word)
		{
			m_letters.push_back(new AvoGUI::TextView{ this, FONT_SIZE, std::string(1, character) });
			m_letters.back()->setSize(LETTER_WIDTH, LETTER_HEIGHT);
			m_letters.back()->getText().setTextAlign(AvoGUI::TextAlign::Center);
			m_letters.back()->setColor(Colors::primary);
			m_letters.back()->setIsVisible(false);
			if (m_letters.size() > 1)
			{
				m_letters.back()->setLeft(m_letters[m_letters.size() - 2]->getRight());
			}
		}
		setSize(m_letters.back()->getRight(), LETTER_HEIGHT);
	}
};

//------------------------------

class GridLetterView : public AvoGUI::View
{
private:
	AvoGUI::Text m_text;

public:
	void handleSizeChange() override
	{
		m_text.setCenter(getSize() * 0.5f);
	}
	void draw(AvoGUI::DrawingContext* p_context) override
	{
		p_context->setColor(Colors::primary);
		p_context->drawText(m_text);
	}

	uint32 column;
	uint32 row;
	char letter;

	GridLetterView(AvoGUI::View* p_parent, char p_letter, uint32 p_column, uint32 p_row) :
		View{ p_parent },
		m_text{ getDrawingContext()->createText(std::string(1, p_letter), 30.f) },
		column{ p_column },
		row{ p_row },
		letter{ p_letter }
	{
		enableMouseEvents();
		setCursor(AvoGUI::Cursor::Hand);
	}
};

class AlphabetGrid : public AvoGUI::View
{
public:
	inline static const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static constexpr uint32 COLUMNS = 10;
	static constexpr uint32 ROWS = 3;
	static constexpr float LETTER_WIDTH = 35.f;
	static constexpr float LETTER_HEIGHT = 35.f;

private:
	std::array<GridLetterView*, COLUMNS*ROWS> m_letters;
public:	
	auto& getLetters()
	{
		return m_letters;
	}

	AlphabetGrid(AvoGUI::View* p_parent) :
		View{ p_parent, { 0.f, 0.f, COLUMNS * LETTER_WIDTH, ROWS * LETTER_HEIGHT } }
	{
		enableMouseEvents();
		for (uint32 a = 0; a < COLUMNS * ROWS; a++)
		{
			m_letters[a] = a < ALPHABET.size() ? new GridLetterView{ this, ALPHABET[a], a % COLUMNS, a / COLUMNS } : nullptr;
			if (m_letters[a])
			{
				m_letters[a]->setSize(LETTER_WIDTH, LETTER_HEIGHT);
				m_letters[a]->setTopLeft(m_letters[a]->column * LETTER_WIDTH, m_letters[a]->row * LETTER_HEIGHT);
			}
		}
	}
};

//------------------------------

class Game : public AvoGUI::View
{
public:
	Game(AvoGUI::View* p_parent, float p_meanDifficulty, float p_standardDeviationDifficulty) :
		View{ p_parent }
	{
		enableMouseEvents();

		auto container = new AvoGUI::View{ this };

		auto dyingMan = new DyingMan{ container };
		auto guessedWord = new GuessedWord{ container, p_meanDifficulty, p_standardDeviationDifficulty };
		guessedWord->setTop(dyingMan->getBottom() + 15.f);
		auto alphabetGrid = new AlphabetGrid{ container };
		alphabetGrid->setTop(guessedWord->getBottom() + 4.f);
		
		container->setPadding(0);
		for (auto child : *container)
		{
			child->setCenterX(container->getWidth()/2);
		}

		sizeChangeListeners += [=](auto...) { container->setCenter(getSize() / 2); };

		for (auto letter : alphabetGrid->getLetters()) 
		{
			if (letter) 
			{
				letter->mouseDownListeners += [=](AvoGUI::MouseEvent const&) {
					letter->setIsVisible(false);
					if (guessedWord->guessLetter(letter->letter))
					{
						if (guessedWord->getHasWon())
						{
							getGui()->addTimerCallback([=] {
								auto app = getParent<App>();
								app->closeScreen();
								app->launchScreen(new GameOver{ app, true, p_meanDifficulty, p_standardDeviationDifficulty });
							}, 1000);
						}
					}
					else if (dyingMan->bringCloserToDeath())
					{
						guessedWord->showAllLetters();
							
						getGui()->addTimerCallback([=] {
							auto app = getParent<App>();
							app->closeScreen();
							app->launchScreen(new GameOver{ app, false, p_meanDifficulty, p_standardDeviationDifficulty });
						}, 1500);
					}
				};
			}
		}
	}
};
