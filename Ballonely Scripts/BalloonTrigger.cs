using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BalloonTrigger : MonoBehaviour
{
	public GameObject balloon;
	public GameObject player;

    // Position where the balloon lerps towards
	public Transform endPosition;

    // UI text that will be displayed when the player hasn't collected enough butterflies
	public GameObject errorSign;

	private bool riseUp = false;
    private float position;

    private void Start ()
    {
		errorSign.SetActive(false);
	}

	private void Update ()
    {
		if (riseUp)
        {
            position += Time.deltaTime;

            // Balloon rises from current position to end position
			balloon.transform.position = Vector3.Lerp (balloon.transform.position, 
			endPosition.position, position);

            // Player rises from current position to end position
			player.transform.position = Vector3.Lerp (player.transform.position,
			endPosition.position, position);
		}
	}

	void OnTriggerStay (Collider col)
    {
        // Is col a player and has it collected enough butterflies?
		if (col.CompareTag("Player") && ButterflyCounter.score >= 10)
        {
			riseUp = true;
		} else
        {
			riseUp = false;
			errorSign.SetActive(true);
		}
	}

	private void OnTriggerExit (Collider col)
    {
		errorSign.SetActive(false);
	}
}
