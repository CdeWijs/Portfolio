using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CollectibleRotation : MonoBehaviour
{
    private Collectible collectibleScript;

    private void Start()
    {
        collectibleScript = FindObjectOfType<Collectible>();
    }

    void FixedUpdate ()
    {
        transform.Rotate(new Vector3(15, 30, 25) * Time.deltaTime);
    }

    public void OnTriggerEnter(Collider col)
    {
        if (col.CompareTag("Player"))
        {
            collectibleScript.PickUp();
        }
    }
}
