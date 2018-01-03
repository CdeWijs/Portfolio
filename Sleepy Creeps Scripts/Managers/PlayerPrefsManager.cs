using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerPrefsManager : MonoBehaviour
{
	const string MASTER_VOLUME_KEY = "master_volume";
    const string HIGH_SCORE_KEY = "high_score";

	public static void SetMasterVolume (float volume)
    {
		if (volume >= 0f && volume <= 1f)
        {
			PlayerPrefs.SetFloat (MASTER_VOLUME_KEY, volume);
		}
        else
        {
			Debug.LogError ("Master volume out of range");
		}
	}

	public static float GetMasterVolume ()
    {
		return PlayerPrefs.GetFloat (MASTER_VOLUME_KEY);
	}

    public static void SetHighScore (int score)
    {
        if (score > PlayerPrefs.GetInt(HIGH_SCORE_KEY))
        {
            PlayerPrefs.SetInt(HIGH_SCORE_KEY, score);
        }
    }

    public static float GetHighScore ()
    {
        return PlayerPrefs.GetInt(HIGH_SCORE_KEY);
    }
}
