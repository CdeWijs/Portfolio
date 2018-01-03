using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Platform : MonoBehaviour
{
    public float speed;
    public GameObject startPosition;
    public GameObject endPosition;
    public GameObject lift;

    private bool inTrigger;
	
	void Update ()
    {
		if (!inTrigger)
        {
            transform.position = Vector3.Lerp(lift.transform.position, startPosition.transform.position, speed);
        }
	}

    private void OnTriggerStay(Collider other)
    {
       if (other.tag == "Player")
        {
            inTrigger = true;
            transform.position = Vector3.Lerp(lift.transform.position, endPosition.transform.position, speed);
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.tag == "Player")
        {
            inTrigger = false;
        }
    }


}
