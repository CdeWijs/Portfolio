using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RevolverControl : MonoBehaviour
{
    public GameObject revolver;
    public AudioClip[] clipArray;
    public bool playedGun;

    private CameraRaycast cameraRaycast;
    private StampControl stampControl;
    private AudioSource audioSource;
    private int currentIndex = 0;
    private bool playingAudio = false;

    void Start ()
    {
        cameraRaycast = FindObjectOfType<CameraRaycast>();
        stampControl = FindObjectOfType<StampControl>();
        audioSource = GetComponent<AudioSource>();
    }

	void Update ()
    {
        stampControl.CheckForInput();

        if (StampControl.clickedOnObject == revolver)
        {
            PlayAudio(0);
            if (!audioSource.isPlaying)
            {
                PlayAudio(1);
                playedGun = true;
            }
        }
    }

    void PlayAudio (int index)
    {
        if (index == currentIndex)
        {
            audioSource.clip = clipArray[index];
            audioSource.Play();
            currentIndex++;
        }
    }
}
