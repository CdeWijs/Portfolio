using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WallTrigger : MonoBehaviour
{

    public GameObject[] deactivateArray;

    private MeshRenderer meshRenderer;

    private void OnTriggerEnter(Collider other)
    {
       foreach(GameObject gObject in deactivateArray)
        {
            meshRenderer = gObject.GetComponent<MeshRenderer>();
            meshRenderer.enabled = false;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        foreach (GameObject gObject in deactivateArray)
        {
            meshRenderer = gObject.GetComponent<MeshRenderer>();
            meshRenderer.enabled = true;
        }
    }
}
