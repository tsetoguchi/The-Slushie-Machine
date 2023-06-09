#pragma once

#include <JuceHeader.h>


class FilmStripKnob : public juce::Slider
{
public:

	FilmStripKnob() : numFrames_(0), isHorizontal_(true) {
		frameWidth = 0;
		frameHeight = 0;
	};

	FilmStripKnob(juce::Image image, const int numFrames, const bool stripIsHorizontal, int index)
		: Slider(juce::String(index)),
		filmStrip(image),
		numFrames_(numFrames),
		isHorizontal_(stripIsHorizontal)
	{
		setTextBoxStyle(NoTextBox, 0, 0, 0);
		setSliderStyle(RotaryVerticalDrag);
		frameHeight = filmStrip.getHeight() / numFrames_;
		frameWidth = filmStrip.getWidth();
		setRange(0.0f, 1.0f, 0.001f);

		getProperties().set(juce::Identifier("index"), index);
	};

	void paint(juce::Graphics& g) override
	{
		int value = (int)((getValue() - getMinimum()) / (getMaximum() - getMinimum()) * (numFrames_ - 1));
		if (isHorizontal_)
		{
			g.drawImage(filmStrip, 0, 0, getWidth(), getHeight(),
				value * frameWidth, 0, frameWidth, frameHeight);
		}
		else
		{
			g.drawImage(filmStrip, 0, 0, getWidth(), getHeight(),
				0, value * frameHeight, frameWidth, frameHeight);
		}
	}

private:
	juce::Image filmStrip;
	const int numFrames_;
	const bool isHorizontal_;
	int frameWidth, frameHeight;
};
