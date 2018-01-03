using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RadioController : MonoBehaviour
{

    public AudioClip clipEscape;                    // "Don't listen to them. What you see isn't real..."

    private AudioSource audioSource;
    private bool playedClipEscape = false;

	void Start ()
    {
        audioSource = GetComponent<AudioSource>();
	}

	void Update ()
    {
		if (StampControl.clickedOnObject == gameObject && !playedClipEscape)
        {
            audioSource.clip = clipEscape;
            audioSource.Play();
            playedClipEscape = true;
        }
	}
}
