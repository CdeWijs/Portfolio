using System.Collections;
using System.Collections.Generic;
using UnityEngine;

enum StampColour
{
    RED,
    GREEN
}

public class CameraInteractiveObject : MonoBehaviour
{
    private const float MAX_GAZE_DURATION = 1.5f;

    // Declare in the inspector:
    public GameObject stampRed;
    public GameObject stampGreen;
    public GameObject paper;

    private GameObject interactiveObject;
    private float gazeTime;

    private Animator animator;
    private string currentAnimatorTrigger;

    private StampColour stampColour;

    private void Start()
    {
        interactiveObject = null;
        gazeTime = 0;
        animator = GetComponentInChildren<Animator>();
    }

    private void Update()
    {
        // Send a raycast directly from the camera
        RaycastHit hit;
        if (Physics.Raycast(new Ray(transform.position, transform.forward), out hit, 50))
        {
            // If the player looks at an interactive object, assign it to the variable
            if (hit.collider.gameObject.tag == "Interactive Object")
            {
                interactiveObject = hit.collider.gameObject;
            }

            if (interactiveObject != null)
            {
                // Check if the player is still looking at the same object as in the last frame
                if (interactiveObject == hit.collider.gameObject)
                {
                    gazeTime += Time.deltaTime;
                    // make sure gazeTime can't be higher than maxGazeDuration
                    if (gazeTime > MAX_GAZE_DURATION)
                    {
                        gazeTime = MAX_GAZE_DURATION;
                    }

                    // Change the colour of the object the player is looking at gradually over 1 second
                    float colourValue = (MAX_GAZE_DURATION - gazeTime) / MAX_GAZE_DURATION;
                    ColourObject(interactiveObject, new Color(1f, colourValue, colourValue));
                    // Check if player clicks on interactable object and handle it
                    HandleMouseClick(colourValue);
                }
                else
                {
                    // If the player isn't looking at the object, change the colour back to white
                    ResetColour();
                }
            }
        }
        else
        {
            if (interactiveObject != null)
            {
                ResetColour();
            }
            interactiveObject = null;
        }
    }

    private void HandleMouseClick(float colourValue)
    {
        if (Input.GetMouseButtonDown(0))
        {
            StampInteraction();
            PaperInteraction(colourValue);
        }
    }

    private void StampInteraction()
    {
        if (interactiveObject == stampRed)
        {
            currentAnimatorTrigger = "stempelRood";
            stampColour = StampColour.RED;
        }
        else if (interactiveObject == stampGreen)
        {
            currentAnimatorTrigger = "stempelGroen";
            stampColour = StampColour.GREEN;
        }
    }

    private void PaperInteraction(float colourValue)
    {
        if (interactiveObject == paper)
        {
            if (currentAnimatorTrigger != null)
            {
                animator.SetTrigger(currentAnimatorTrigger);
                if (stampColour == StampColour.RED)
                {
                    ColourObject(interactiveObject, new Color(1f, colourValue, colourValue));
                }
                else
                {
                    ColourObject(interactiveObject, new Color(colourValue, 1f, colourValue));
                }
            }
        }
    }

    private void ResetColour()
    {
        ColourObject(interactiveObject, Color.white);
        gazeTime = 0;
    }

    private void ColourObject(GameObject gameObject, Color color)
    {
        if (gameObject != null)
        {
            Renderer objectRenderer = gameObject.GetComponent<Renderer>();
            if (objectRenderer != null)
            {
                objectRenderer.material.color = color;
            }
        }
    }
}
