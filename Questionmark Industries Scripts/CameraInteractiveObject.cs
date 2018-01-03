using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraInteractiveObject : MonoBehaviour
{
    public GameObject stempelRood;
    public GameObject stempelGroen;
    public GameObject papier;

    private GameObject interactiveObject;
    private float gazeTime;
    private float maxGazeDuration = 1.5f;
    private Animator animator;
    private string currentAnimatorTrigger;
    private bool isStempelRood;

    void Start()
    {
        interactiveObject = null;
        gazeTime = 0;
        animator = GetComponentInChildren<Animator>();
    }

    void Update()
    {
        // I'm aware how awful this is
        RaycastHit hit;
        if (Physics.Raycast(new Ray(transform.position, transform.forward), out hit, 50))
        {
            if (interactiveObject != null)
            {
                if (interactiveObject == hit.collider.gameObject)
                {
                    gazeTime += Time.deltaTime;
                    if (gazeTime > maxGazeDuration) gazeTime = maxGazeDuration;
                    
                    float color = (maxGazeDuration - gazeTime) / maxGazeDuration;
                    ColorObject(interactiveObject, new Color(1f, color, color));

                    if (Input.GetMouseButtonDown(0))
                    {
                        Debug.Log("clicked on " + interactiveObject);
                        if (interactiveObject == stempelRood)
                        {
                            currentAnimatorTrigger = "stempelRood";
                            isStempelRood = true;
                        }
                        else if (interactiveObject == stempelGroen)
                        {
                            currentAnimatorTrigger = "stempelGroen";
                            isStempelRood = false;
                        }

                        if (interactiveObject == papier)
                        {
                            if (currentAnimatorTrigger != null)
                            {
                                animator.SetTrigger(currentAnimatorTrigger);
                                if (isStempelRood)
                                {
                                    ColorObject(interactiveObject, new Color(1f, color, color));
                                } else
                                {
                                    ColorObject(interactiveObject, new Color(color, 1f, color));
                                }
                            }
                        }
                    }
                }
                else
                {
                    ColorObject(interactiveObject, Color.white);
                    gazeTime = 0;
                }
            }
            
            if (hit.collider.gameObject.tag == "Interactive Object")
            {
                interactiveObject = hit.collider.gameObject;
                Debug.Log(interactiveObject);
            }

        }
        else
        {
            if (interactiveObject != null)
            {
                ColorObject(interactiveObject, Color.white);
                gazeTime = 0;
            }
            
            interactiveObject = null;
        }
    }

    void ColorObject(GameObject gameObject, Color color)
    {
        if (gameObject == null) return;
        
        Renderer objectRenderer = gameObject.GetComponent<Renderer>();
        if (objectRenderer != null) objectRenderer.material.color = color;
    }

}
