using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AudioTimer : MonoBehaviour
{
    public AudioClip[] clipArray;
    public bool interruptResistance = false;

    private RevolverControl revolverControl;
    private IntercomController intercomController;
    private AudioSource audioSource;
    public float time = 0;
    private int currentIndex = 0;

	void Start ()
    {
        revolverControl = FindObjectOfType<RevolverControl>();
        intercomController = FindObjectOfType<IntercomController>();
        audioSource = GetComponent<AudioSource>();
	}
	
	void Update ()
    {
        if (revolverControl.playedGun && intercomController.playedIntercom)
        {
            time += Time.deltaTime;
        }

        // first minute
        if (time >= 15) { PlayClip(0); }
        if (time >= 25) { PlayClip(1); }
        if (time >= 35) { PlayClip(2); }
        if (time >= 40) { PlayClip(3); }
        if (time >= 50) { PlayClip(4); }
        if (time >= 60) { PlayClip(5); }

        // second minute
        if (time >= 65) { PlayClip(6); }
        if (time >= 70) { PlayClip(7); interruptResistance = true; }

        // third minute
        if (time >= 100) { PlayClip(8); }
        if (time >= 110) { PlayClip(9); }
        if (time >= 120) { PlayClip(10); }
        if (time >= 130) { PlayClip(11); }
        if (time >= 140) { PlayClip(12); }
        if (time >= 150) { PlayClip(13); }
        if (time >= 160) { PlayClip(14); }
        if (time >= 170) { PlayClip(16); }
    }

    void PlayClip (int index)
    {
        if (index == currentIndex)
        {
            audioSource.clip = clipArray[index];
            audioSource.Play();
            currentIndex++;
        }
    }
}
