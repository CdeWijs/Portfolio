using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class OptionsController : MonoBehaviour
{
	public Slider volumeSlider;
	public LevelManager levelManager;

	private MusicPlayer musicPlayer;

	void Start ()
    {
		musicPlayer = FindObjectOfType<MusicPlayer>();
		volumeSlider.value = PlayerPrefsManager.GetMasterVolume ();
	}

	void Update ()
    {
		musicPlayer.ChangeVolume(volumeSlider.value);
	}

	public void SaveAndExit ()
    {
		PlayerPrefsManager.SetMasterVolume (volumeSlider.value);
		SceneManager.LoadScene ("Start");
	}

	public void SetDefaults ()
    {
		volumeSlider.value = 0.5f;
	}
}
