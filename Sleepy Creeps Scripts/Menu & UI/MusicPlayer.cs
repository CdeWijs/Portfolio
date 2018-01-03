using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MusicPlayer : MonoBehaviour
{
    static MusicPlayer instance = null;

    public AudioClip[] levelMusic;

    private AudioSource audioSource;
    private AudioClip currentAudio;

    void Awake()
    {
        if (instance != null)
        {
            Destroy(gameObject);
        }
        else
        {
            instance = this;
            GameObject.DontDestroyOnLoad(gameObject);
        }
    }

    void Start()
    {
        audioSource = GetComponent<AudioSource>();
        audioSource.volume = PlayerPrefsManager.GetMasterVolume();
        currentAudio = audioSource.clip;
        SceneManager.sceneLoaded += OnLevelLoaded;
    }

    void OnLevelLoaded(Scene scene, LoadSceneMode mode)
    {
        AudioClip audioClip = levelMusic[scene.buildIndex];

        if (audioClip != currentAudio && audioClip != null)
        {
            audioSource.clip = audioClip;
            audioSource.loop = true;
            audioSource.Play();
            currentAudio = audioClip;
        }
    }

    public void ChangeVolume(float volume)
    {
        audioSource.volume = volume;
    }
}
