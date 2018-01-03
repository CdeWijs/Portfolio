using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StampControl : MonoBehaviour
{
    public static int stampCount = 0;

    public GameObject stempelRoodBureau;        
    public GameObject stempelGroenBureau;      
    public GameObject stempelRoodHand;          
    public GameObject stempelGroenHand;         
    public GameObject papierPrefab;                   // prefab(!) van papier
    public GameObject papierPosition;

    public static GameObject clickedOnObject;         // laatste object waarop geklikt is
    private GameObject papierInstance;
    private CameraRaycast cameraRaycast;
    private Animator animatorStempels;
    private Animator animatorPapier;
    private bool isStempelRood;                 // true wanneer op rode stempel is geklikt
    private string currentAnimatorTrigger;
    private Color papierKleur;
    private float timeStamp;
    private float coolDown = 2f;

	void Start ()
    {
        cameraRaycast = FindObjectOfType<CameraRaycast>();
        animatorStempels = GetComponent<Animator>();

        stempelRoodHand.SetActive(false);
        stempelGroenHand.SetActive(false);

        InstantiatePaper();
    }

	void Update ()
    {
        CheckForInput();

        // checkt of er op de rode stempel is geklikt
        if (clickedOnObject == stempelRoodBureau)
        {
            isStempelRood = true;
            SetStampActive();
            currentAnimatorTrigger = "stempelRood";
            papierKleur = new Color(1f, 0, 0);
        }

        // checkt of er op de groene stempel is geklikt
        if (clickedOnObject == stempelGroenBureau)
        {
            isStempelRood = false;
            SetStampActive();
            currentAnimatorTrigger = "stempelGroen";
            papierKleur = new Color(0, 1f, 0);
        }

        // checkt of er op het papier is geklikt
        if (clickedOnObject == papierInstance)
        {
            Debug.Log("Play Stamp Animation");
            StampPaper();
            clickedOnObject = null;
            
        }
	}

    public void CheckForInput()
    {
        // checkt of de linkermuisknop is ingedrukt
        if (Input.GetMouseButtonDown(0))
        {
            // zet variable naar het object wat met de raycast gezien wordt
            clickedOnObject = cameraRaycast.interactiveObject;
        }
    }

    void StampPaper()
    {
        // checkt of er een stempel geselecteerd is
        if (currentAnimatorTrigger != null && timeStamp <= Time.time)
        {
            animatorStempels.SetTrigger(currentAnimatorTrigger);
            papierInstance.GetComponent<Renderer>().material.color = papierKleur;
            stampCount++;
            
            // veeg het papier weg en instantiate een nieuw papier
            Invoke("SwipePaper", 1f);
            Invoke("InstantiatePaper", 2f);
            timeStamp = Time.time + coolDown;
        }
    }

    void SwipePaper()
    {
        animatorPapier = papierInstance.GetComponent<Animator>();
        animatorPapier.SetTrigger("papierSwipe");
    }

    void InstantiatePaper()
    {
        papierInstance = Instantiate(papierPrefab, papierPosition.transform) as GameObject;
    }

    void SetStampActive ()
    {
        if (isStempelRood)
        {
            stempelRoodHand.SetActive(true);
            stempelGroenHand.SetActive(false);

            // make the red stamp on desk invisible
            stempelRoodBureau.SetActive(false);
            stempelGroenBureau.SetActive(true);
        }
        else
        {
            stempelRoodHand.SetActive(false);
            stempelGroenHand.SetActive(true);

            // make the green stamp on desk invisible
            stempelRoodBureau.SetActive(true);
            stempelGroenBureau.SetActive(false);
        }
    }
}
