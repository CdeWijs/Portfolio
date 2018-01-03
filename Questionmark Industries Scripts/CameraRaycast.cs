using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraRaycast : MonoBehaviour
{
    public GameObject interactiveObject;
    public GameObject particles;

    private StampControl stampControl;
    private Shader standardShader;
    private Shader illuminateShader;
    private bool illuminateObject;

	void Start ()
    {
        standardShader = Shader.Find("Standard");
        illuminateShader = Shader.Find("Legacy Shaders/Reflective/Specular");
        interactiveObject = null;
        particles.SetActive(false);
	}

	void Update ()
    {
        RaycastHit hit;
        if (Physics.Raycast(new Ray(transform.position, transform.forward), out hit, 50))
        {
            // If raycast hits an interactive object, set variable
            if (hit.collider.gameObject.tag == "Interactive Object")
            {
                interactiveObject = hit.collider.gameObject;
                Debug.Log(interactiveObject);
            }

            // If raycast hit an interactive object in previous frame
            if (interactiveObject != null)
            {
               
                // If raycast hits the same object again
                if (interactiveObject == hit.collider.gameObject)
                {
                    illuminateObject = true;
                }
                else
                {
                    illuminateObject = false;
                }
            }
        }

        // if raycast doesn't hit anything, but variable exists
        else if (interactiveObject != null)
        {
            illuminateObject = false;
        }

        TurnOnParticles();
    }

    void TurnOnParticles()
    {
        if (interactiveObject != null)
        {
           
            if (illuminateObject)
            {
                particles.SetActive(true);
            }
            else
            {
                particles.SetActive(false);
            }
        }
    }
}
