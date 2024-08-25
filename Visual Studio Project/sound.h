#pragma once
#include <SFML/Audio.hpp>
#include <iostream>



void deathMusic()
{
    sf::Music music;
    music.openFromFile("death.mp3");
    music.play();
    // while the music is playing
    while (music.getStatus() == sf::Music::Playing)
    {
        // leave some CPU time for other processes
        sf::sleep(sf::milliseconds(100));
    }
}

void jumpMusic()
{
    sf::Music music;
    music.openFromFile("jump.mp3");
    music.play();
    // while the music is playing
    while (music.getStatus() == sf::Music::Playing)
    {
        // leave some CPU time for other processes
        sf::sleep(sf::milliseconds(100));
    }
}

void openingMusic()
{
    sf::Music music;
    music.openFromFile("opening.MP3");
    music.play();
    // while the music is playing
    while (music.getStatus() == sf::Music::Playing)
    {
        // leave some CPU time for other processes
        sf::sleep(sf::milliseconds(100));
    }
}

void ramboShootMusic()
{
    sf::Music music;
    music.openFromFile("ramboshoot.MP3");
    music.play();
    // while the music is playing
    while (music.getStatus() == sf::Music::Playing)
    {
        // leave some CPU time for other processes
        sf::sleep(sf::milliseconds(100));
    }
}

void tankShootMusic()
{
    sf::Music music;
    music.openFromFile("tankshot.MP3");
    music.play();
    // while the music is playing
    while (music.getStatus() == sf::Music::Playing)
    {
        // leave some CPU time for other processes
        sf::sleep(sf::milliseconds(100));
    }
}

void victoryMusic()
{
    sf::Music music;
    music.openFromFile("victory.MP3");
    music.play();
    // while the music is playing
    while (music.getStatus() == sf::Music::Playing)
    {
        // leave some CPU time for other processes
        sf::sleep(sf::milliseconds(100));
    }


}

void crateMusic()
{
    sf::Music music;
    music.openFromFile("crate.MP3");
    music.play();
    // while the music is playing
    while (music.getStatus() == sf::Music::Playing)
    {
        // leave some CPU time for other processes
        sf::sleep(sf::milliseconds(100));
    }


}