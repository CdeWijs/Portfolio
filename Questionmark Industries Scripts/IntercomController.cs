using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IntercomController : MonoBehaviour
{
    public AudioClip clipGood;              // "We see that you're doing what's asked of you. Good. Compliance will be rewarded."
    public AudioClip clipExcuseUs;          // 4. "Excuse us for the malfunction. This defiance will be fixed shortly."
    public AudioClip clipCostProductivity;   // 6. "Don't make us replace you."
    public bool playedIntercom;

    private AudioTimer audioTimerScript;
    private AudioSource audioSource;
    private bool playedClipGood = false;
    private bool playedClipExcuse = false;
    private bool playedClipProductivity = false;

	void Start ()
    {
        audioTimerScript = FindObjectOfType<AudioTimer>();
        audioSource = GetComponent<AudioSource>();
	}

	void Update ()
    {
		if (StampControl.stampCount >= 5 && !playedClipGood)
        {
            audioSource.clip = clipGood;
            audioSource.Play();
            playedClipGood = true;
            playedIntercom = true;
        }

        if (audioTimerScript.interruptResistance && !playedClipExcuse)
        {
            Invoke("Interrupt", 2);
            if (!audioSource.isPlaying && !playedClipProductivity)
            {
                Invoke("FollowUp", 8);
            }
        }
	}

    void Interrupt ()
    {
        audioSource.clip = clipExcuseUs;
        audioSource.Play();
        playedClipExcuse = true;
    }

    void FollowUp ()
    {
        audioSource.clip = clipCostProductivity;
        audioSource.Play();
        playedClipProductivity = true;
    }
}
